# my_own_STL_cpp
This STL Does not depend on any standard library, which means that codes can be reused in any circumstance.
The code, as a part of my practice, is achieved by c++. The whole relationship is shown in the readme.md.
In this code, class Object is the base class, which reloads keywords of new and delete.


             StaticQueue    Search_tree  ←  Tree   →   Ave_tree     StaticStack
                          ↖                 ↑                  ↗
              ListQueue   ←  Queue       ← Object  →    Stack    →  ListStack
                                              ↓
                           Matrix_Graph  ← Graph → List_Graph
			   
			   
	        StaticLinkList           CircleLinkList
			      ↖      ↗  
		                LinkList               DualList  →  DualCircleList
					  ↖      ↗
	          Dynamic_array	             List	       Shared_ptr
                                 ↖           ↑           ↗	
			           Array  ← Object → Pointer   
                                 ↙           ↓           ↘
	           Static_array    	     Vector	      Smart_ptr
                                         ↙       ↘
                            Static_vector            Dynamic_vector



