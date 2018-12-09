import networkx as nx
import matplotlib.pyplot as plt

G = nx.DiGraph()
f = open("inputs/day7")
edges = []
for l in f.readlines():
    splited = l.split()
    step = splited[7]
    dep = splited[1]
    edges.append((dep,step))
G.add_edges_from(edges)

def longestChainFrom(G, n):
    if not G.predecessor(n):
        return 1
    else:
        return 1 + max(map(lambda node : longestChainFrom(G,node), G.predecessor()))

print("Longest chain :", max(map(lambda node : longestChainFrom(G,node), G.nodes())))


pos = nx.spring_layout(G)
nx.draw_networkx_nodes(G, pos)
nx.draw_networkx_labels(G, pos)
nx.draw_networkx_edges(G, pos)
plt.show()
