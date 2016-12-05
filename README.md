anser - a boolean propagator network framework
----------------------------------------------

'Anser' is a small framework for the creation of boolean logic
computation networks from C++ integer expressions. Expression
variables are input/output terminals into the computation networks.
Once a network has been created, it is omni-directional; all
computations that have sufficient information to be computed *will* be
computed and output to the relvant termals (variables) of the network.

Once a network is built, information can be entered 'bit by bit' for
the input variables, and the computation graph can be analyzed for
changes in the network.  I feel this could provide relvant insight and
information into the breaking of hash functions or the existance of
one way functions.

Why?
----

I originally wrote this with the idea of using it to analyze the
computational strutures of hash funtions.  Using this library, one can
setup arbitrary computations into a graph and selectively insert
information into it.  This partial insertion of information was
thought to lead to insignts into the structure of the computation of
the hash function.

By analyzing the changes in the nodes in the graph, it was thought
that one could use this 'emergent' information in the system to glean
possible ways to find collisions or other flaws within the function.

This libary could also be used to do digital logic design at the
And/Or/Not gate level.

Classes
-------

Op
UnOp
BinOp

Wire
WireNotSetException
WireContradictionException

Id : UnOp
Not : UnOp
And : BinOp
Or: BinOp
Xor: BinOp
HalfAdder: Op
FullAdder: Op

Bus

Example
-------

#include "anser.h"

int main(void) {
    Bus a, b, c;

    c = a + b;
}

--
Burton Samograd
burton.samograd@gmail.com
2016