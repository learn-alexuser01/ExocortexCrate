#ifndef _ALEMBIC_WRITE_JOB_H_
#define _ALEMBIC_WRITE_JOB_H_

#include "AlembicObject.h"

#include "CommonRegex.h"

class AlembicWriteJob
{
private:
    MString mFileName;
    MObjectArray mSelection;
    std::vector<double> mFrames;
    Abc::OArchive mArchive;
	Abc::OObject mTop;
    unsigned int mTs;
    std::map<std::string,std::string> mOptions;
    //std::vector<AlembicObjectPtr> mObjects;
    std::map<std::string, AlembicObjectPtr> mapObjects;
	double mFrameRate;
public:
   AlembicWriteJob(
      const MString & in_FileName,
      const MObjectArray & in_Selection,
      const MDoubleArray & in_Frames);
   ~AlembicWriteJob();

   // to change the name of objects while exporting!
   SearchReplace::ReplacePtr replacer;

   Abc::OArchive GetArchive() { return mArchive; }
   Abc::OObject GetTop() { return mTop; }
   const std::vector<double> & GetFrames() { return mFrames; }
   const MString & GetFileName() { return mFileName; }
   unsigned int GetAnimatedTs() { return mTs; }
   void SetOption(const MString & in_Name, const MString & in_Value);
   bool HasOption(const MString & in_Name);
   MString GetOption(const MString & in_Name);
   AlembicObjectPtr GetObject(const MObject & in_Ref);
   bool AddObject(AlembicObjectPtr in_Obj);
   size_t GetNbObjects() { return mapObjects.size(); }
 
   MStatus PreProcess();
   MStatus Process(double frame);
   bool forceCloseArchive(void);
};

class AlembicExportCommand : public MPxCommand
{
  public:
    AlembicExportCommand();
    virtual ~AlembicExportCommand();

    virtual bool isUndoable() const { return false; }
    MStatus doIt(const MArgList& args);

    static MSyntax createSyntax();
    static void* creator();
};

#endif