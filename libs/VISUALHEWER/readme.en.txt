Visual Hever 1.0
(containing brain Hewer24)

Executing
---------
Check for occurrence files plocha.dat and tah.dat before program executing.


Passing the solution tree 
-------------------------
Execute the program. You can pass the solution 
tree on the page Tree View. Every node is evaluated
by numbers pn (proof number - number of nodes needed
 to investigate for prooving the win) and dn
(disproof number - number of nodes needed
to investigate to prooving the loss). Infinite is
sign as -1. Node being unable to expand is terminal
and evaluation function can diagnose win or loss in
it. You can move in the tree by mouse or keyboard (arrows).

External AI moves
-----------------
You can consult (how the AI would turn) every situation (active node) with external AI by presing key 1-9 by presing (in 1-9 second timeout). 


Situation import and export
---------------------------
You can also export the situation (active node) into files plocha.dat and tah.dat. You can also import entirely new situation as the root situation.

Page Threat
--------------
There are represented threat on the page Threat, which can arise by moving onto the given field, left for black and right for white. Coord numbered by rows and are represented as z=x+y*20
Cn=Number of stone remainding to place in, to have a five. Tn=Number of stone remainding to place in, to make a treat undefendable, Tn takes into account only local defend moves, it doesn't take into account global countemoves.


Loss analyze
--------------
Visual Hewer can match external AI and after potencial loss can analyze it's reason (shortage of thinking time or missing the opponenets move by movegenerator). This function is disabled in this version due to bugs.

Others
------
The Move generator is entirely same as Hewer24's being use in Gomocup 2004 tournament, 
there are some small simplifications by pn and dn inicialization due to better transparentness.

Program weakness
----------------
Bad start, openbook missing (the next reason of bad start), imperfect evaluation function (bad middlegame strategy). And other general weaknesses of pn-search algoritm (AI can't defend, AI can attack only, underestimation of pn a dn, memory problems).

Strong points
-------------
Can find out the win even 19 moves beforehand (in 5 seconds on celeron 400Mhz).
Fast and accurate evaluation function, accurate movegenerator by defending. 


Tomáš Kubeš
5.4. 2004
<tomas_kubes@seznam.cz>