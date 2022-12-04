



## Graph of the network described in the Lectures

            #A  B  C  D  E  F  G  H
vertex   = [[0, 1, 0, 0, 0, 0, 1, 0],   #A
            [1, 0, 1, 0, 1, 0, 0, 0],   #B  
            [0, 1, 0, 1, 0, 1, 0, 0],   #C
            [0, 0, 1, 0, 0, 0, 0, 1],   #D
            [0, 1, 0, 0, 0, 1, 1, 0],   #E
            [0, 0, 1, 0, 1, 0, 0, 1],   #F
            [1, 0, 0, 0, 1, 0, 0, 1],   #G
            [0, 0, 0, 1, 0, 1, 1, 0]]   #H
            #A  B  C  D  E  F  G  H    
edge     = [[0, 2, 0, 0, 0, 0, 6, 0],   #A
            [2, 0, 7, 0, 2, 0, 0, 0],   #B
            [0, 7, 0, 3, 0, 3, 0, 0],   #C
            [0, 0, 3, 0, 0, 0, 0, 2],   #D
            [0, 2, 0, 0, 0, 2, 1, 0],   #E
            [0, 0, 3, 0, 2, 0, 0, 2],   #F
            [6, 0, 0, 0, 1, 0, 0, 4],   #G
            [0, 0, 0, 2, 0, 2, 4, 0]]   #H


# node state class with variables, predecessor node, length to predecessor, and wether the node has tried every neighboring node
class state:
    def __init__(self):
        self.pred=-1
        self.length=9999999
        self.label='tenative'
    



#function
def dijkstra(nodes,distance,start,end):
    
    #list of all nodes and their respective states
    nodeState=[]
    
    #number of total nodes
    numNodes=len(nodes[0])
    
    #Initilize all nodes 
    for i in range(numNodes):
        nodeState.append(state())
    #Initialize the starting node  
    nodeState[start].length=0
    nodeState[start].label='permanent'    
    
    
    
    #k is the working node, Start off with starting node
    k=start
    
    #loop through all nodes
    loop1=True
    while loop1:
        #if there is a neighboring node
        for i in range(numNodes):
            if nodes[k][i]!=0 and nodeState[i].label=='tenative':
                #if the distance is shorter than the previously know length update the node and its predecessor
                if nodeState[k].length + distance[k][i] < nodeState[i].length:
                    nodeState[i].pred=k
                    nodeState[i].length=nodeState[k].length+ distance[k][i]
                    
        #reset variable k        
        k=0
        if start==end:
            mindistance=0
        else:
            mindistance=99999999
            
        #go through all the nodes and update the mindistance
        for i in range(numNodes):
            if nodeState[i].label== 'tenative' and nodeState[i].length < mindistance:
                mindistance=nodeState[i].length
                k=i
        nodeState[k].label='permanent'
        if k== end:
            loop1=False
    loop2=True

    # Get the path starting from the end node to the start node
    k=end
    path=[]
    while loop2:
        
        path.append(k)
        k=nodeState[k].pred
        if k<=-1:
            loop2=False
    #flip the list so it reads start->finish
    path.reverse()
    
    #Map the node number to the Letter like in the lectures
    for i in range(len(path)):
        path[i]=chr(ord('@')+path[i]+1)
   
    print("The Shortest Path from ", chr(ord('@')+start+1)," to ",chr(ord('@')+end+1)," is ", mindistance)
    print("Through the Path:",path)
    
    
                
#################################END OF FUNCTION###########################  

begin=0
for i in range(len(vertex)):                
    dijkstra(vertex,edge,begin,i)
              
      
    

    
    
    
    
    
    
    

    
    
    
    
    
    
    
    
    
       
   






