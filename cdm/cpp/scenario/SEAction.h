/**************************************************************************************
Copyright 2015 Applied Research Associates, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License. You may obtain a copy of the License
at:
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
**************************************************************************************/

#pragma once
CDM_BIND_DECL(ActionData);
class SESubstanceManager;

class DLL_DECL SEAction : public Loggable
{
public:

  SEAction();
  virtual ~SEAction();

  virtual void Clear();// Deletes all members
  
  /** Test if the action has all data it needs */
  virtual bool IsValid() const { return true; }
  /** Actions can be turned off or on with various data combinations
  *  This method will encapsulate that logic in a single function */
  virtual bool IsActive() const { return IsValid(); }

  static SEAction* newFromBind(const CDM::ActionData& action, SESubstanceManager& substances);

  virtual bool Load(const CDM::ActionData& in);
  virtual CDM::ActionData* Unload() const;
protected:
  void Unload(CDM::ActionData& data) const;

public:

  virtual std::string GetComment() const;
  virtual void SetComment(const std::string& comment);
  virtual bool HasComment() const;
  virtual void InvalidateComment();

  virtual void ToString(std::ostream &str)const=0;

protected:

  std::string           m_Comment;
};  

inline std::ostream& operator<< (std::ostream& out, const SEAction& a) 
{
    a.ToString(out);
    return out;
}