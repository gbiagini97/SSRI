In a typical IT corporate scenario there are some defined Security Policies that protect resources and services from indiscriminate operations.

In this project we define a MAC Policy built around the secrecy-based Bell-LaPadula model.

Subjects (users) have a distinct authorization level from a role hierarchy:
* Administrator
* Manager
* Guest
  
Objects (resources) have distinct secrecy levels:
* Top-Secret
* Secret
* Public

Policy:
* Users with the Administrator level can register new users by assigning them credentials and an authorization level (role);
* Newly created users authenticate via assigned credentials and need to change their password after the first login;
* Users request an Access Token that expires after one hour in order to access services;
* The services entrypoint verify that the user has a valid and non-expired Access Token and that has the necessary claims to access the requested service;
* The requested service allow the user to perform operations (read, update) based on the user's role on the data.


The project has three main components:
* Identity Access Manager: Performs a Role Based Authentication for registered users and provides them an Access Token to interact with the services. Administrators can create new users;
* Gateway: Handles requests and allow users to access the services based on their role;
* Sensible Data Service: The driver that allows users to access the data stored on a secured database based on their role.