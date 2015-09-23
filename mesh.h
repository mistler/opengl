#ifndef MESH_H
#define MESH_H


class Mesh
{
public:
    virtual ~Mesh();
    virtual void render() = 0;
};

#endif // MESH_H
