# SWM-Project

## Context
In a typical IT corporate scenario there are some defined Security Policies that protect resources and services from indiscriminate operations.

## Policy
In this project we define a MAC Policy referring to the secrecy-based **Bell-LaPadula model** as the source of inspiration:

The key principle of the policy is a **Role-Based Access Control** for subjects and objects:

* Subjects:
  * **Users**: have a distinct authorization level from a _role hierarchy_:
    * Administrator;
    * Manager;
    * Guest.
  * **Services**: are allowed to retrieve only the information their role allows to. The role name matches the service name.
  
* Objects:
  * **Resources**: have distinct _secrecy levels_:
    * Top-Secret;
    * Secret;
    * Public.
  * **Endpoints**: require an authorization level based on the Users _role hierarchy_.

Services retrieve information based on their role from a **centralized secret-manager**. They have the _least privilege requirement_ to access the platform secrets.

Policy:
* The platform implies a strong _separation of duties_ for each service;
* Services have the _least privilege requirement_ to access only secrets of their area of competence from a **centralized secret-manager**;
* Services authenticate with the secret-manager that leases a **Token** for subsequent service calls for information retrieval;
* Users with the Administrator level can register new users by _assigning them credentials and an authorization level_ (role);
* Newly created users authenticate via assigned credentials and _need to change their password_ after the first login;
* Users request an **Access Token** that _expires_ after a pre-defined time (eg. one hour) in order to access services;
* The services entrypoint verify that the user has a valid and non-expired Access Token and that has the necessary **claims** to access the requested service via the endpoint;
* The requested service allow the user to perform operations (read, update) based on the user's role on the data.

## Mechanism
The project has three main services entirely developed from scratch:
* Identity Access Manager: 
  * Stores encrypted credentials and users roles;
  * Performs a Role Based Authentication;
  * Administrators can register new users;
  * Provides an Access Token to authenticated users in order to interact with services;
* Gateway: 
  * Is the main entrypoint that handles incoming requests for services;
  * Verifies the validity of the Access Token and extracts the claims from it;
  * Allow users to access services if their role is sufficient;
* Sensible Data Service:
  * Handles gateway requests;
  * Allow users to access the data based on their role from the database.

The three services login at their startup with a centralized secret-manager via their distinct `role_id` and `secret_id`. The secret-manager responds to the login request with a `Token`  so that they can retrieve only the necessary parameters to operate.

The Access Token that will be used is described in the [RFC-7519](https://tools.ietf.org/html/rfc7519) which is a representation of a set of claims that matches the user's authorization level.