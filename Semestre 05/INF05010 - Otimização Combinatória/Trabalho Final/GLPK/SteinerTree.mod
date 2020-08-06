# Start Node
param StartNode, integer, >0;

# Number of Nodes
param NumNodes, integer, >0;

# Number of Edges
param NumEdges, integer, >0;

# Number of Terminals
param NumTerminals, integer, >0;

# Set of Nodes
set Nodes := {1..NumNodes};

# set of Edges: start_node, end_node, edge_cost
set Edges, dimen 3;

# set of Terminals
set Terminals, dimen 1;

# Costs
set Costs := setof{(i,j,c) in Edges} c;

# Undirected Edges of the graph
set E := setof{(i,j,c) in Edges} (i,j);
set Etwisted := setof{(i,j,c) in Edges} (j,i);

# Bidirected Edges of the graph
set B := E union Etwisted;

# Assignment
var x{E}, binary;

# Flows
var f {(i,j) in B, k in Terminals diff {StartNode}}, binary;

# Objective Function
minimize Obj: sum{(i,j,c) in Edges} c * x[i,j];

s.t. flows{j in Nodes, k in Terminals diff {StartNode}}:
	(sum{(i,j) in B} f[i,j,k]) - (sum{(i,j) in B} f[j,i,k]) = 
	(if j = StartNode then -1 else if j = k then 1 else 0);
		
s.t. implication{(i,j) in E, k in Terminals diff {StartNode}}:
f[i,j,k] <= x[i,j];

s.t. notNegative{(i,j) in B, k in Terminals diff {StartNode}}:
f[i,j,k] >= 0;

# Uncomment in case of divergent result. It seems not to be helpful.
s.t. implicationReverse{(i,j) in E, k in Terminals diff {StartNode}}:
f[j,i,k] <= x[i,j];

end;