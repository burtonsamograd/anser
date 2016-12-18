anser - a boolean propagator network framework
----------------------------------------------

'Anser' is a small framework for the creation of boolean logic
computation networks from C++ expressions.  Such networks are
collections of 'wires' (terminals) that connect 'ops' (gates) to
specify boolean functions.

The created networks are non-directional; all computations *will* be
computed and output to the relvant terminal of the computation network
given sufficient information on the remaining termnals.

Information can be entered 'bit by bit' into the terminals, and the
computation graph can then be analyzed for changes in the network.  By
analyzing the changes in the nodes in the graph, it was thought that
one could use this 'emergent' information in the system to glean find
interesting information within the function that is being analyzed.

This libary could also be used to do digital logic design at the
And/Or/Not gate level.

Motivation
----------

By building compuation graphs, one can see the actual logical inner
workings of compuational functions.  This in itself is fascinating.

The main intent of this tool was to create a system to help with the
cracking of hash functions, or at least to learn more about hash
functions along the way.  By analyzing the inner workings and lattice
logic structures of existing hash functions and their informational
flow analysis as bits are entered, we could find flaws or
optimizations and help build future generations of systems.

I want to make a suite of logic design tools that will allow me to
generate the plans for a CPU or some other piece of logic hardware.

Example
-------

```c
#include "anser.h"

int main(int argc, char** argv) {
    // Declare the I/O terminals for our network
    Bus a, b, c;

    // Define/build the computation network
    c = a + b;

    // Evaluate the network by setting terminal values.
    // Compute b, by setting a and c.
    c.set(3);
    a.set(1);

    // Make sure we're correct.
    assert(b.get() == 2);
}
```

Examples
--------

The following contain more complex examples of the system:

tests.cpp	: basic tests for computational networks.

sha256.cpp	: a (mostly) unmodified sha256 implemementation and test;
 		  changes were made to variable types to allow for the use of anser.

Graph Traversal
---------------

Wires offer the functions 'size' and 'nth', allowing for one to
retrieve the connetion Ops of the wire.

UnOps have get_in() and get_out() to retrieve thier terminal Wires.

BinOps have get_in1(), get_in2() and get_out() to retrieve thier
terminal Wires.

Ops have more than 1 or 2 input/output terminals and follow the above
convention.

Classes
-------

Wire		- a communication channel for connecting inputs and output termninal on a *Op

Bus	   	- a bundle of 'Wires', 32 by default to be used as integer expression variables
                  utilizing the overloaded integer operations to build the computation networks

--

UnOp		- 1 terminal operation

BinOp 		- 2 terminal operation

Op 		- n terminal operation

--

Id : UnOp	- input passes through to output

Not : UnOp 	- output = !input

And : BinOp	- output = input1 & input2

Or: BinOp	- output = input1 | input2

Xor: BinOp	- output = input1 ^ input2

HalfAdder: Op	- half adder with a, b, outputs sum and carry

FullAdder: Op   - full adder with a, b, carry, outputs sum and carry

The Use of The Bus
------------------

Busses are abstractions over top of the above lower level logic
machinery used to create computation graphs from ordinary mathematical
expressions.  A bus can be thought of as a variable in your integer
equation, but it is bi-directional...generally.  Here's an example:

    Bus a, b, c;	// define busses

    c = a + b;		// build graph

    a = 1, c = 4;	// submit partial information

    assert(b == 3);	// check result is correct

As you can see from the above example, we defined the equation one way
like one would normally compute it in a programming language, but
could solve for values on the right hand side of the equals, unlike a
normal programming expression.

This works with arbitrary integer expressions and data.  The
penultimate example so far is SHA256, included in the examples.  There
is also an unpublished experiement with performing the bitcoin double
SHA256 hash function and mining operation and computing it correctly.

Graph Analysis
--------------

The intention of this project is to create a tool for building and
debugging logic networks with the hopes of architecting a computation
system.  As this tool is meant to create computation graphs, as
complete set of graph analysis tools and utilities are going to be
needed.

But.

They might not be found here. This project is a derivative of a 'lisp'
project I have been interested in over the years (see references
below).  The design tools for the computer architecture I am planning
are going to be written in Common Lisp; this project is going to be
the 'execution engine' for the simuation.  Really, this project is an
implementation of the Scheme projects found SICP chapter 3.

It runs faster since it is written in C++.

The real design intention of this project is to be the core runtime of
a graph analysis and generation toolkit written in Common Lisp, with
the goal of such a toolkit to be the creation and analysis of digital
logic machines, such as computers.

References
----------

The Art of the Propagator (TAOTP) by Alexy Radul and Gerald Jay Sussman: http://web.mit.edu/~axch/www/art.pdf

Structure and Interpretation of Computer Programs (SICP):

- A Simulator for Digital Circuits: https://mitpress.mit.edu/sicp/full-text/book/book-Z-H-22.html#%_sec_3.3.4

- Propagation of Constraints: https://mitpress.mit.edu/sicp/full-text/book/book-Z-H-22.html#%_sec_3.3.5

--
Burton Samograd
burton.samograd@gmail.com
2016