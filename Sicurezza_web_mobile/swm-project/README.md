# SWM-Project

## Overview
This project purpose is to build a **Single-Sign-On platform** inspired by the **MILS** (Multiple Independent Levels of Security/Safety) security architecture which is built upon the secrecy based **Bell-LaPadula model** and **William Wulf**'s works.

MILS is a high assurance security architecture that supports the coexistence of untrusted and trusted components, based on verifiable separation mechanisms and controlled information flow.

William Wulf, in his work about [HYDRA - The kernel of a multiprocessor operating system](https://dl.acm.org/doi/10.1145/355616.364017), references the need of a strong separation between protection and security when referring to access control systems, a concept that Bell-LaPadula principles lack.

In his paper he stated:
> Protection is a Mechanism, security is a Policy. 
> 
> A system utilizing such a mechanism may be more or less secure depending upon policies governing the use of the mechanism and upon the reliability of the program which manipulate the protected entities. 
> 
> [...]
> 
> A particular consequence of this philosophy is to discard the notion of 'ownership'. 
> While ownership is useful concept for certain "security" strategies, to include a concept at the most primitive levels would lead to the exclusion of the construction of certain other classes of truly secure systems.
 

## Policy
The policy is a **Claim-Based Access Control** for Subjects and Objects abandoning the hierarchical Role-Based system:

* Subjects: 
  * Have one or multiple _claims_ that declare what the Subject is or is not, defining what _realm(s)_ it can have access to. 
  * Once the authentication process is performed, Subjects are given an **Access Token**, that _expires_ after a pre-defined and configurable time, for submitting requests for Objects;
  * Subjects can register to the SSO indipendently and verify their claims by submitting valuable information that vouch for the declared claims;
* Objects: are defined into a distinct _realm_, grouped by the nature of the resource.

A MILS system employs a set of properties, commonly acronymed as **NEAT**:
* Non-bypassable: each component of the system must use a pre-defined and non-modifiable communication path/pattern;
* Evaluatable: any component must be evaluated to the level of assurance required of that component;
* Always-invoked: each and every access/message is checked by the appropriate security monitors;
* Tamperproof: the system prevents unauthorized changes to the security monitor code, configuration and data.

The _NE_ properties imply a strong _separation of duty_ for each component of the SSO.

The AT properties implies the need of many _security-managers_ with a defined _scope_ that are constantly monitoring every request of their scope and are being constantly monitored by all others security-managers to prevent hacking or tweaking.


## Mechanism
MILS systems are in-line with current Cloud development patterns so the SSO revolves around 3 microservices built from scratch and a secret manager:
* [Identity Access Manager](iam/README.md): stores encrypted credentials and users claims;
* Gateway: main entrypoint that handles incoming requests for services verifing the validity of the Access Token and the necessary claims to access the service realm;
* Data Service: stores data based on it's realm;
* [HashiCorp Vault](vault/README.md): secret manager that services need to authenticate with in order to retrieve services connection parameters and credentials.

The communication pattern of choice in microservices is gRPC and every component is completely testable to guaranteee the level of assurance required.

The three services perform authentication at their startup with Vault via their distinct `role_id` and `secret_id`. Vault responds to the login request with an `Access Token`  that they can use to retrieve only the necessary parameters to operate.

Services will lookup for parameters changes on Vault every minute in order to adapt to the context. If an invalid secret is written on Vault or a service can't access to it anymore, an error log will be thrown to make the platform mantainers aware of a possible attack.

Users perform registration indipendently via a dedicated endpoint on the Gateway that delegates the request to the Identity Access Manager. A subsequent valid login requests with `user's credentials` will return an `Access Token`.

Only registration and login endpoints on the Gateway are accessible without a valid `Access Token`, described in the [RFC-7519](https://tools.ietf.org/html/rfc7519), which is the representation of the user's verified claims.

Accessing a realm is possible by verifing the claims submitted in the registration phase and this is only possible by providing the requested information about each claim.