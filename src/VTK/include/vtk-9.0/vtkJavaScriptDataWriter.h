/*=========================================================================

  Program:   ParaView
  Module:    vtkJavaScriptDataWriter.h

  Copyright (c) Kitware, Inc.
  All rights reserved.
  See Copyright.txt or http://www.paraview.org/HTML/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/*-------------------------------------------------------------------------
  Copyright 2009 Sandia Corporation.
  Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
  the U.S. Government retains certain rights in this software.
-------------------------------------------------------------------------*/

/**
 * @class   vtkJavaScriptDataWriter
 * @brief   A Javascript data writer for vtkTable
 * Writes a vtkTable into a Javascript data format.
 */

#ifndef vtkJavaScriptDataWriter_h
#define vtkJavaScriptDataWriter_h

#include "vtkIOCoreModule.h" // For export macro
#include "vtkWriter.h"

class vtkStdString;
class vtkTable;

class VTKIOCORE_EXPORT vtkJavaScriptDataWriter : public vtkWriter
{
public:
  static vtkJavaScriptDataWriter* New();
  vtkTypeMacro(vtkJavaScriptDataWriter, vtkWriter);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  //@{
  /**
   * Get/set the name of the Javascript variable that the dataset will be assigned to.
   * The default value is "data", so the javascript code generated by the filter will
   * look like this: "var data = [ ... ];". If VariableName is set to nullptr, then no
   * assignment statement will be generated (i.e., only "[ ... ];" will be generated).
   */
  vtkSetStringMacro(VariableName);
  vtkGetStringMacro(VariableName);
  //@}

  //@{
  /**
   * Get/Set the filename for the file.
   */
  vtkSetStringMacro(FileName);
  vtkGetStringMacro(FileName);
  //@}

  //@{
  /**
   * Get/Set the whether or not to include field names
   * When field names are on you will get data output
   * that looks like this:
   * var data=[
   * {foo:3,time:"2009-11-04 16:09:42",bar:1 },
   * {foo:5,time:"2009-11-04 16:11:22",bar:0 },
   * without field names the data will be an array
   * of arrays like this:
   * var data=[
   * [3,"2009-11-04 16:09:42",1],
   * [5,"2009-11-04 16:11:22",0],

   * Default is ON (true)
   */
  vtkSetMacro(IncludeFieldNames, bool);
  vtkGetMacro(IncludeFieldNames, bool);
  //@}

  // Get/Set the OutputStream for writing output.
  void SetOutputStream(ostream* my_stream);
  ostream* GetOutputStream();

protected:
  vtkJavaScriptDataWriter();
  ~vtkJavaScriptDataWriter() override;

  bool OpenFile();
  void CloseFile();

  void WriteData() override;
  virtual void WriteTable(vtkTable* table, ostream* stream_ptr);

  // see algorithm for more info.
  // This writer takes in vtkTable.
  int FillInputPortInformation(int port, vtkInformation* info) override;

  char* VariableName;
  char* FileName;
  bool IncludeFieldNames;
  ostream* OutputStream;

private:
  vtkJavaScriptDataWriter(const vtkJavaScriptDataWriter&) = delete;
  void operator=(const vtkJavaScriptDataWriter&) = delete;

  ostream* OutputFile;
};

#endif
