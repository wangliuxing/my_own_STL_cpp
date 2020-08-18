# my_own_STL_cpp




StaticLinkList          CircleLinkList
              ↖      ↗           
					     LinkList              DualList  →  DualCircleList
                         ↖      ↗
	 Dynamic_array		        List			      Shared_ptr
                ↖           ↑           ↗	
					       Array  ← Object → Pointer   
                ↙           ↓           ↘
	 Static_array    	       Vector			      Smart_ptr
                        ↙       ↘
           Static_vector            Dynamic_vector

             StaticQueue	  Search_tree  ←  Tree   →   Ave_tree     StaticStack
                          ↖                 ↑                  ↗
              ListQueue   ←  Queue       ← Object  →    Stack    →  ListStack
                                              ↓
                           Matrix_Graph  ← Graph → List_Graph

