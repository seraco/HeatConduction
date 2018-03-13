#ifndef __CMESH_H
#define __CMESH_H

#include "CMatrix.h"
#include "CGeometry.h"

class CMesh {
    private:
        unsigned nXDirElem;
        unsigned nYDirElem;
        unsigned nElem;
        unsigned nNode;
        unsigned nNodePerElem;
        unsigned dofPerNode;
        unsigned totalDofInElem;
        CGeometry geometry;

    public:
        CMesh();
        CMesh(const unsigned NElx, const unsigned NEly, const CGeometry geo);
        virtual ~CMesh();

        unsigned getNXDirElem();
        unsigned getNYDirElem();
        unsigned getNElem();
        unsigned getNNode();
        unsigned getNNodePerElem();
        unsigned getDofPerNode();
        unsigned getTotalDofInElem();
        CGeometry getGeometry();

        CMatrix coordinateMtx();
};

#endif
