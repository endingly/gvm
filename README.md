# gvm introduction

## 0. Introduction and build guide

gvm is a virtual machine of GPGPU, and it is a emulator in one word. 

if you want to build gvm, you can follow the steps below:

> Install the dependencies:
>
> the dependencies of gvm would be managed by *vcpkg*, so you only need to install vcpkg and then install the dependencies by running cmake.
>
> the dependencies of gvm should be recorded in the `vcpkg.json` file.

## 1. Project Structure

- `application`
  
  The application layer of gvm, including the user interface and the backend.

- `core`
  
  The core layer of gvm, including the virtual machine and the emulator.

- `common`

  The common layer of gvm, including the common modules and the common tools.