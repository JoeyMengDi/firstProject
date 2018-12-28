
/* 
 * Copyright (c) Castles Technology Co., Ltd. 
 * 
 * File:   KeyBoard.cpp
 * Author: Alan.Ren
 *
 * Created: 2017/07/26
 * 
 */

#include <semaphore.h>
#include <pthread.h>

#include "KeyBoard.h"
#include "ErrorCode.h"

static BOOL s_bInitSem = FALSE;
static sem_t s_cSem;

static void InitSem()
{
    if (!s_bInitSem)
    {
        sem_init(&s_cSem, 0, 1);
        s_bInitSem = TRUE;
    }
}

/////////////////////////////////////////////////////////////////////////////////
// CKeyBoard
//
// Function:
//          Construct function.
//
// @param:
//          None.
//
// @return:
//          None
/////////////////////////////////////////////////////////////////////////////////
CKeyBoard::CKeyBoard():
m_bKBDSingleUse(FALSE)
{
    if (!s_bInitSem)
    {
        InitSem();
    }
}



/////////////////////////////////////////////////////////////////////////////////
// ~CKeyBoard
//
// Function:
//          Deconstruct function.
//
// @param:
//          None.
//
// @return:
//          None.
/////////////////////////////////////////////////////////////////////////////////
CKeyBoard::~CKeyBoard()
{
    Unlock();
}



/////////////////////////////////////////////////////////////////////////////////
// KBDHit
//
// Function:
//          Read a key value.
//
// @param:
//          [OUT] pbyKey: For saving read key.
//
// @return:
//          d_OK - Successfully read ok
//          Other values - please refer CTOSAPI.h
/////////////////////////////////////////////////////////////////////////////////
WORD CKeyBoard::KBDHit(OUT PBYTE pbyKey)
{
    if (pbyKey == NULL)
    {
        return ERROR_INVALID_PARAM;
    }
    if (!m_bKBDSingleUse)
    {
        *pbyKey = d_KBD_INVALID;
        if (sem_trywait(&s_cSem) == 0)
        {
            m_bKBDSingleUse = TRUE;
        }
        return d_OK;
    }
    return CTOS_KBDHit(pbyKey);
}



/////////////////////////////////////////////////////////////////////////////////
// KBDGet
//
// Function:
//
// @param:
//
// @return:
// 
/////////////////////////////////////////////////////////////////////////////////
WORD CKeyBoard::KBDGet(PBYTE pbyKey)
{
    if (NULL == pbyKey)
    {
        return ERROR_INVALID_PARAM;
    }
    if (!m_bKBDSingleUse)
    {
        Lock();
    }
    return CTOS_KBDGet(pbyKey);
}



/////////////////////////////////////////////////////////////////////////////////
// Lock
//
// Function:
//          Lock keyboard and other user can not get key value.
//
// @param:
//          None.
//
// @return:
//          None
/////////////////////////////////////////////////////////////////////////////////
void CKeyBoard::Lock()
{
    if (!m_bKBDSingleUse)
    {
        sem_wait(&s_cSem);
        m_bKBDSingleUse = TRUE;
    }
}



/////////////////////////////////////////////////////////////////////////////////
// Unlock
//
// Function:
//          Unlock keyboard and other user cna get key value.
//
// @param:
//          None.
// 
// @return:
//          None
/////////////////////////////////////////////////////////////////////////////////
void CKeyBoard::Unlock()
{
    if (m_bKBDSingleUse)
    {
        sem_post(&s_cSem);
        m_bKBDSingleUse = FALSE;
    }
}