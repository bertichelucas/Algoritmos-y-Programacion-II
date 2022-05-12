class UnionFind():
    def __init__(self, l):
        self.groups = {}
        for elem in l:
            self.groups[elem] = elem

    def find(self, v):
        if self.groups[v] == v:
            return v
        
        real_group = self.find(self.groups[v])
        self.groups[v] = real_group
        return real_group
    
    def union(self, u, v):
        new_group = self.find(u)
        other = self.find(v)
        self.groups[other] = new_group