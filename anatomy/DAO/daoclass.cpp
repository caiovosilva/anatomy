#include "daoclass.h"

DAOClass::DAOClass()
{
    _mydb = DBConnection::Instance()->Connection();
}
