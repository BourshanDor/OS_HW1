# Simulated OS Multi-Level Page Table Implementation
This project involves the implementation of simulated OS code that handles a multi-level (trie-based) page table. The code provides functions for creating/destroying virtual memory mappings and querying the mappings in the page table. The implementation targets an imaginary 64-bit x86-like CPU.

## Introduction
The goal of this project is to simulate an operating system's handling of a multi-level page table using trie-based data structures. By implementing the provided functions, the code allows for the management of virtual memory mappings and retrieval of physical addresses based on virtual addresses.

## Target Hardware
The simulated OS is designed to run on a 64-bit x86-like CPU architecture. The virtual address space consists of 64 bits, with the lower 57 bits used for address translation. Physical addresses also utilize 64 bits.

### Virtual Addresses
Virtual addresses are structured as follows:
![Alt text](https://github.com/BourshanDor/OS_HW1/blob/2d5aa898def0e917865b8f48483ebef7c5891149/Pictures/Screenshot%202023-06-13%20185301.png "Virtual address")

### Physical Addresses
Physical addresses share the same 64-bit size as virtual addresses.
## Page Table Structure

The page/frame size is set to 4 KB (4096 bytes), and page table nodes occupy a physical page frame of the same size. Each page table entry is 64 bits long. The least significant bit (bit 0) represents the valid bit, while bits 1-11 are unused and should be set to zero. The top 52 bits store the page frame number that the entry points to.










