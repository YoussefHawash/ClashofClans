#ifndef NODE_H
#define NODE_H

class Node
{
public:
    int x;
    int y;
    float weight;
    int type;
    Node(int a=0,int b=0,int c=0,int t=0);
    void makeitgrass(float i){weight=i;};
};

#endif // NODE_H
