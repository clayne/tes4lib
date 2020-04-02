/*===========================================================================
 *
 * File:	Textutils.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __TEXTUTILS_H
#define __TEXTUTILS_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "oberrorhandler.h"
  #include "dl_map.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Shortcuts to help define a static text replacement array */
  #define BEGIN_TEXTREPLACE(Name) const textreplace_t Name[] = {
  #define ADD_TEXTREPLACE(Variable, Value) { Variable, Value }, 
  #define END_TEXTREPLACE() { 0, NULL } };

	/* Shortcuts to help define a static string-value array */
  #define BEGIN_STRINGVALUE(Name) extern const stringvalue_t Name[]; CObStringValueMap Name##Map(Name); const stringvalue_t Name[] = {
  #define ADD_STRINGVALUE(Value, String) { Value, String }, 
  #define END_STRINGVALUE() { 0, NULL } };

	/* Whether to use the advanced map class in some places */
  #define OB_USESTRINGVALUEMAP 1

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Structure used when replacing variables in a text string */
  struct textreplace_t {
	const SSCHAR* pVariable;	/* These are references to strings */
	const SSCHAR* pValue;
   };

	/* Holds information on simple string-value association */
  struct stringvalue_t {
  	int	      Value;
	const SSCHAR* pString;
   };

  typedef TGenRefPtrMap<const SSCHAR*, int,    const SSCHAR*> CObStringMap;
  typedef TGenRefPtrMap<int,           SSCHAR, int>           CObValueMap;

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObStringValueMap Definition
 *
 * Simple map for looking up string/value pairs.
 *
 *=========================================================================*/
class CObStringValueMap {

  /*---------- Begin Private Class Members ----------------------*/
private:
  CObStringMap         m_StringMap;
  CObValueMap          m_ValueMap;

  const stringvalue_t* m_pStringValues;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Initialize the maps from the current value array */
  bool Initialize (void);


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObStringValueMap(const stringvalue_t* pValues) {
	m_pStringValues = pValues;
	Initialize();
  }

  ~CObStringValueMap() { Destroy(); }

  void Destroy (void) {
	m_StringMap.Destroy();
	m_ValueMap.Destroy();
	m_pStringValues = NULL;
  }

  const SSCHAR* FindValue  (const int     Value)    { return m_ValueMap.Lookup(Value); }

  int FindString (const SSCHAR* pString)  { 
    const int* pResult = m_StringMap.Lookup(pString); 
    if (pResult != NULL) return (*pResult); 
    return (0);
  }

  int FindString (const SSCHAR* pString, const int Default)  { 
    const int* pResult = m_StringMap.Lookup(pString); 
    if (pResult != NULL) return (*pResult); 
    return (Default);
  }

  bool FindString (int& Value, const SSCHAR* pString)  { 
    const int* pResult = m_StringMap.Lookup(pString); 
    if (pResult != NULL) return (false); 
    Value = *pResult;
    return (true);
  }
};
/*===========================================================================
 *		End of Class CObStringValueMap Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Definitions
 *
 *=========================================================================*/

  const SSCHAR* FindTextVariable (const SSCHAR* pString, const textreplace_t ReplaceInfo[]);
  
  const SSCHAR* FindStringValue  (const int Value,       const stringvalue_t StringInfo[]);
  int           FindStringValue  (const SSCHAR* pString, const stringvalue_t StringInfo[]);

  bool          FindStringValue  (int& OutputValue, const SSCHAR* pString, const stringvalue_t StringInfo[]);
  bool          FindStringValue  (const SSCHAR** ppString, const int Value, const stringvalue_t StringInfo[]);

  bool ReplaceTextVariables (CSString& DestString, const CSString& SrcString, const textreplace_t ReplaceInfo[]);

	/* Hexadecimal conversion functions */
  char        ConvertToHexChar     (const dword Value);
  const char* ConvertByteToHexChar (const byte  Value);
  byte        ConvertFromHexByte   (const char* pHexByte);
  dword       ConvertFromHexChar   (const char HexChar);

/*===========================================================================
 *		End of Function Definitions
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Textutils.H
 *=========================================================================*/
