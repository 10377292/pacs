// @HEADER
// ***********************************************************************
// 
//                      Didasko Tutorial Package
//                 Copyright (2005) Sandia Corporation
// 
// Under terms of Contract DE-AC04-94AL85000, there is a non-exclusive
// license for use of this work by or on behalf of the U.S. Government.
// 
// This library is free software; you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; either version 2.1 of the
// License, or (at your option) any later version.
//  
// This library is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//  
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA
//
// Questions about Didasko? Contact Marzio Sala (marzio.sala _AT_ gmail.com)
// 
// ***********************************************************************
// @HEADER

// Use of Epetra_FECrsMatrix
// This code should be run with at least two processes

#include "Didasko_ConfigDefs.h"

#ifdef HAVE_DIDASKO_EPETRA

#include "Epetra_ConfigDefs.h"
#ifdef HAVE_MPI
#include "mpi.h"
#include "Epetra_MpiComm.h"
#else
#include "Epetra_SerialComm.h"
#endif
#include "Epetra_Map.h"
#include "Epetra_Vector.h"
#include "Epetra_FECrsMatrix.h"

// =========== //
// main driver //
// ----------- //

int main(int argc, char *argv[]) {

#ifdef HAVE_MPI
  MPI_Init(&argc, &argv);
  Epetra_MpiComm Comm(MPI_COMM_WORLD);
#else
  Epetra_SerialComm Comm;
#endif

  // Create a linear map of size 10 (could be any number > 1)
  //
  // Note that a linear map is distributed approximately evenly over
  // all processors.
  //
  int NumGlobalElements = 10;
  Epetra_Map Map(NumGlobalElements,0,Comm);

  // create a diagonal FE crs matrix (one nonzero per row)
  Epetra_FECrsMatrix A(Copy,Map,1);
  
  // Next, set the matrix entries.
  //
  // Note 1: Matrix entries are only contributed from processor
  // 0, regardless of how many processors the program is running on.
  // Proc 0 fills the entire global matrix. Data that belongs in
  // matrix rows owned by procs 1 .. numprocs-1 gets sent to those
  // processors during the call to 'A.GlobalAssemble()' below.
  // 
  // Note 2: We fill the matrix using 'InsertGlobalValues'. An
  // alternative approach that would be more efficient for large
  // matrices in most cases would be to first create and fill a
  // graph (Epetra_FECrsGraph), then construct the matrix with the
  // graph (after calling graph.FillComplete) and fill the matrix
  // using the method 'SumIntoGlobalValues'.
  // 
  if( Comm.MyPID() == 0 ) {
    for( int i=0 ; i<NumGlobalElements ; ++i ) {
      int index = i;
      double value = 1.0*i;
      A.InsertGlobalValues(1,&index,&value);
    }
  }
  
  A.GlobalAssemble();

  cout << A;
  
#ifdef HAVE_MPI
  MPI_Finalize();
#endif

  return(EXIT_SUCCESS);

}

#else

#include <stdlib.h>
#include <stdio.h>
#ifdef HAVE_MPI
#include "mpi.h"
#endif

int main(int argc, char *argv[])
{
#ifdef HAVE_MPI
  MPI_Init(&argc,&argv);
#endif

  puts("Please configure Didasko with:\n"
       "--enable-epetra");

#ifdef HAVE_MPI
  MPI_Finalize();
#endif
  return 0;
}
#endif


