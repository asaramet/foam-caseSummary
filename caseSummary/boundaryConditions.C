/*---------------------------------------------------------------------------*\

\*---------------------------------------------------------------------------*/

#include "boundaryConditions.H"
#include "Time.H"
#include "Ostream.H"
#include "IOobjectList.H"

#include "IOdictionary.H"

#include "volFields.H"
#include "surfaceFields.H"
#include "GeometricField.H"
#include "GeoMesh.H"
// * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * * * //

Foam::boundaryConditions::boundaryConditions(const Foam::Time& runTime, const Foam::word& regionName)
:
  runTime_ { runTime },
  regionName_ { regionName }
 {}

// * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * * * //

void Foam::boundaryConditions::write(Foam::Ostream& os) const
{
  // ignore it if no volumetric mesh found
  if (! Foam::fileHandler().isFile(runTime_.constant()/"polyMesh/points"))
  {
    os << "Warning: Can't read boundary conditions as there is no generated volume mesh!" << Foam::endl;
    return;
  }

  // get the volume mesh
  const Foam::fvMesh mesh
  (
    Foam::IOobject
    (
      regionName_,
      runTime_.timeName(0),
      runTime_,
      Foam::IOobject::MUST_READ
    )
  );

  // create a list of field names
  const Foam::wordList fieldNames
  (
    Foam::IOobjectList(mesh, runTime_.timeName()).sortedNames()
  );

  if (fieldNames.empty())
    os << "TODO: HERE YOU MUST GO THROUGH THE REGIONS" << Foam::endl;

  fieldsInfo_(os, mesh, fieldNames);

} // end write(os&)

void Foam::boundaryConditions::fieldsInfo_(Foam::Ostream& os, const Foam::fvMesh& mesh, const Foam::wordList& fieldNames) const
{
  // Create boundary poly mesh object
  const Foam::polyBoundaryMesh& boundaryMesh = mesh.boundaryMesh();
  //const Foam::MESH::BoundaryMesh& boundaryMesh = mesh.boundaryMesh();

  //os << boundaryMesh.findPatchID("inlet") << Foam::endl;
  os << boundaryMesh.headerClassName() << Foam::endl;

  //boundaryMesh.writeData(os);

  forAll(boundaryMesh, i)
  {
    //os << boundaryMesh[i].type() << Foam::tab << boundaryMesh[i].name() << Foam::endl;

    // create the finiteVolume patch
    //const Foam::fvPatch patch {boundaryMesh[i], mesh};
  }

  //Foam::volScalarField::Boundary boundaryField {boundaryMesh};

  // loop through all the field names
  forAll(fieldNames, i)
  {
    // create a field object
    Foam::IOobject field
    (
      fieldNames[i],
      runTime_.timeName(0),
      mesh,
      Foam::IOobject::MUST_READ
    );

  // Get the field class type (ex.: volVectorField)
    //Foam::word fieldClass = field.headerClassName();
    //os.writeEntry(field.name(), fieldClass);

    // display data only if the field is volScalarField
    if (field.typeHeaderOk<Foam::volScalarField>(false))
    //if (field.typeHeaderOk<Foam::kqRWallFunctionFvPatchField>(false))
    {
      // Get the field class type (ex.: volVectorField)
      const Foam::word fieldClass = field.headerClassName();
      os << field.name() << Foam::tab << fieldClass << Foam::endl;

      //Foam::volScalarField::Boundary *boundaryField {new Foam::volScalarField::Boundary(boundaryMesh, field.name())};


      // Create a pointer to the geometric field
      //std::unique_ptr<Foam::volScalarField> geoField { new Foam::volScalarField (field, mesh)};
      //os << geoField->type();
    }
  }
} // end fieldsInfo_(os)
