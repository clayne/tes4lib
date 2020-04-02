/*===========================================================================
 *
 * File:	ObLongsubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Defines the CObLongSubrecord used for storing a 32-bit signed integer.
 *
 *=========================================================================*/
#ifndef __OBLONGSUBRECORD_H
#define __OBLONGSUBRECORD_H


/*===========================================================================
 *
 * Begin Reqiured Includes
 *
 *=========================================================================*/
  #include "obsubrecord.h"
/*===========================================================================
 *		End of Reqiured Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObLongSubrecord Definition
 *
 *=========================================================================*/
class CObLongSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObLongSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  long	m_Value;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { return File.Read(&m_Value, sizeof(long)); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Value, sizeof(long)); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObLongSubrecord() { m_Value = 0; }
  //virtual ~CObLongSubrecord() { Destroy(); }
  virtual void Destroy (void) { m_Value = 0; CObSubrecord::Destroy(); }

 	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObLongSubrecord* pSubrecord1 = ObCastClassNull(CObLongSubrecord, pSubrecord);
	m_RecordSize = sizeof(long);

	if (pSubrecord1 != NULL) {
	  m_Value = pSubrecord1->GetValue();
	}
	else {
	  memset(&m_Value, 0, sizeof(m_Value));
	}
	return (true);
  }

	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObLongSubrecord); }

	/* Initialize a new record */
  virtual void InitializeNew (void) { CObSubrecord::InitializeNew();  m_Value = 0; m_RecordSize = sizeof(dword); }

	/* Bit flag operations */
  bool  CheckFlag (const dword Mask)                  { return CheckFlagBits(m_Value, Mask); }
  void  ClearFlag (const dword Mask)		      { m_Value &= ~Mask; }
  long  FlipFlag  (const dword Mask, const bool Flag) { FlipFlagBits(*(dword *)&m_Value, Mask, Flag); return (m_Value); } 
  void  SetFlag   (const dword Mask)		      { m_Value |= Mask; }

	/* Get class members */
  long          GetValue    (void) { return (m_Value); }
  long*         GetValuePtr (void) { return (&m_Value); }
  long&         GetValueRef (void) { return (m_Value); }
  virtual byte*	GetData     (void) { return (byte *)(&m_Value); }

  	/* Set class methods */
  void SetValue (const long Value) { m_Value = Value; }
 
 };
/*===========================================================================
 *		End of Class CObLongSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObLongSubrecord.H
 *=========================================================================*/
