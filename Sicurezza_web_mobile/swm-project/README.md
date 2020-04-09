# SWM-Project

## Context
In a typical IT corporate scenario there are some defined Security Policies that protect resources and services from indiscriminate operations.

## Policy
In this project we define a MAC Policy built around the secrecy-based **Bell-LaPadula model**:
* Subjects (users) have a distinct authorization level from a role hierarchy:
  * Administrator
  * Manager
  * Guest
  
* Objects (resources) have distinct secrecy levels:
  * Top-Secret
  * Secret
  * Public

Policy:
* Users with the Administrator level can register new users by assigning them credentials and an authorization level (role);
* Newly created users authenticate via assigned credentials and need to change their password after the first login;
* Users request an Access Token that expires after a pre-defined time (eg. one hour) in order to access services;
* The services entrypoint verify that the user has a valid and non-expired Access Token and that has the necessary claims to access the requested service;
* The requested service allow the user to perform operations (read, update) based on the user's role on the data.

## Mechanism
The project has three main components entirely developed from scratch:
* Identity Access Manager: 
  * Performs a Role Based Authentication;
  * Administrators can register new users;
  * Provides an Access Token to authenticated users to interact with the services;
* Gateway: 
  * Is the main entrypoint that handles incoming requests for services;
  * Verifies the validity of the Access Token and extracts the claims from it;
  * Allow users to access services if their role is sufficient;
* Sensible Data Service:
  * Handles gateway requests;
  * Allow users to access the data based on their role from the database.

The Access Token that will be used is described in the [RFC-7519](https://tools.ietf.org/html/rfc7519) which is a representation of a set of claims that matches the user's authorization level.