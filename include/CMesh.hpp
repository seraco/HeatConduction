#ifndef __CMESH_H
#define __CMESH_H

#include "CMatrix.hpp"
#include "CGeometry.hpp"

class CMesh {
    private:
        unsigned nXDirElem;
        unsigned nYDirElem;
        unsigned nElem;
        unsigned nNode;
        unsigned nNodePerElem;
        unsigned dofPerNode;
        unsigned totalDofInElem;
        unsigned nDofTotal;
        CMatrix coorMtx;
        CMatrix topolMtx;
        CMatrix connMtx;
        CMatrix glDofMtx;

        CMatrix coordinateMtx(CGeometry geo);
        CMatrix topologyMtx();
        CMatrix connectivityMtx(CMatrix topol);
        CMatrix globalDofMtx(CMatrix conn);

    public:
        CMesh();
        CMesh(const unsigned NElx, const unsigned NEly, const CGeometry geo);
        virtual ~CMesh();

        unsigned getNXDirElem() const;
        unsigned getNYDirElem() const;
        unsigned getNElem() const;
        unsigned getNNode() const;
        unsigned getNNodePerElem() const;
        unsigned getDofPerNode() const;
        unsigned getTotalDofInElem() const;
        unsigned getNDofTotal() const;
        CMatrix getCoorMtx() const;
        CMatrix getTopolMtx() const;
        CMatrix getConnMtx() const;
        CMatrix getGlDofMtx() const;
};

#endif
