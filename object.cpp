#include "object.h"
#include <math.h>

std::ostream& operator<<(std::ostream& out, const ObjectInteger& obj)
{
    out<< obj.toString();
    return out;
}

std::ostream& operator<<(std::ostream& out, const ObjectDecimal& obj)
{
    out<< obj.toString();
    return out;
}

std::ostream& operator<<(std::ostream& out, const ObjectString& obj)
{
    out<< obj.toString();
    return out;
}


bool DecimalCmpEQ(const double& a, const double& b)
{
    const static double EPSILON = 1e-5;
    return fabs(a - b) < EPSILON;
}

bool ObjectInteger::cmpEQ(const Object* obj) const
{
    bool ret = false;
    switch (obj->getType())
    {
    case TYPE_INT:
        ret = (m_value == ((ObjectInteger*) obj)->getValue());
        break;
    case TYPE_DECIMAL:
        ret = DecimalCmpEQ(m_value, ((ObjectDecimal*) obj)->getValue());
        break;
    default:
        ret = false;
    }
    return ret;
}

bool ObjectInteger::cmpNE(const Object* obj) const
{
    bool ret = true;
    switch (obj->getType())
    {
    case TYPE_INT:
        ret = (m_value != ((ObjectInteger*) obj)->getValue());
        break;
    case TYPE_DECIMAL:
        ret = !DecimalCmpEQ(m_value, ((ObjectDecimal*) obj)->getValue());
        break;
    default:
        ret = true;
    }
    return ret;
}

bool ObjectInteger::cmpLE(const Object* obj) const
{
    bool ret = false;
    switch (obj->getType())
    {
    case TYPE_INT:
        ret = m_value <= ((ObjectInteger*) obj)->getValue();
        break;
    case TYPE_DECIMAL:
        ret = (double)m_value <= ((ObjectDecimal*) obj)->getValue();
        break;
    default:
        ret = false;
    }
    return ret;
}

bool ObjectInteger::cmpLT(const Object* obj) const
{
    bool ret = false;
    switch (obj->getType())
    {
    case TYPE_INT:
        ret = m_value < ((ObjectInteger*) obj)->getValue();
        break;
    case TYPE_DECIMAL:
        ret = (double)m_value < ((ObjectDecimal*) obj)->getValue();
        break;
    default:
        ret = false;
    }
    return ret;
}

bool ObjectInteger::cmpGE(const Object* obj) const
{
    bool ret = false;
    switch (obj->getType())
    {
    case TYPE_INT:
        ret = m_value >= ((ObjectInteger*) obj)->getValue();
        break;
    case TYPE_DECIMAL:
        ret = (double)m_value >= ((ObjectDecimal*) obj)->getValue();
        break;
    default:
        ret = false;
    }
    return ret;
}

bool ObjectInteger::cmpGT(const Object* obj) const
{
    bool ret = false;
    switch (obj->getType())
    {
    case TYPE_INT:
        ret = m_value > ((ObjectInteger*) obj)->getValue();
        break;
    case TYPE_DECIMAL:
        ret = (double)m_value > ((ObjectDecimal*) obj)->getValue();
        break;
    default:
        ret = false;
    }
    return ret;
}


bool ObjectDecimal::cmpEQ(const Object* obj) const
{
    bool ret = false;
    switch (obj->getType())
    {
    case TYPE_INT:
        ret = ((ObjectInteger*) obj)->cmpEQ(this);
        break;
    case TYPE_DECIMAL:
        ret = DecimalCmpEQ(m_value, ((ObjectDecimal*) obj)->getValue());
        break;
    default:
        ret = false;
    }
    return ret;
}

bool ObjectDecimal::cmpNE(const Object* obj) const
{
    bool ret = true;
    switch (obj->getType())
    {
    case TYPE_INT:
        ret = ((ObjectInteger*) obj)->cmpNE(this);
        break;
    case TYPE_DECIMAL:
        ret = !DecimalCmpEQ(m_value, ((ObjectDecimal*) obj)->getValue());
        break;
    default:
        ret = true;
    }
    return ret;
}

bool ObjectDecimal::cmpLE(const Object* obj) const
{
    bool ret = false;
    switch (obj->getType())
    {
    case TYPE_INT:
        ret = !((ObjectInteger*) obj)->cmpGT(this);
        break;
    case TYPE_DECIMAL:
        ret = (double)m_value <= ((ObjectDecimal*) obj)->getValue();
        break;
    default:
        ret = false;
    }
    return ret;
}

bool ObjectDecimal::cmpLT(const Object* obj) const
{
    bool ret = false;
    switch (obj->getType())
    {
    case TYPE_INT:
        ret = !((ObjectInteger*) obj)->cmpGE(this);
        break;
    case TYPE_DECIMAL:
        ret = (double)m_value < ((ObjectDecimal*) obj)->getValue();
        break;
    default:
        ret = false;
    }
    return ret;
}

bool ObjectDecimal::cmpGE(const Object* obj) const
{
    bool ret = false;
    switch (obj->getType())
    {
    case TYPE_INT:
        ret = !((ObjectInteger*) obj)->cmpLT(this);
        break;
    case TYPE_DECIMAL:
        ret = (double)m_value >= ((ObjectDecimal*) obj)->getValue();
        break;
    default:
        ret = false;
    }
    return ret;
}

bool ObjectDecimal::cmpGT(const Object* obj) const
{
    bool ret = false;
    switch (obj->getType())
    {
    case TYPE_INT:
        ret = !((ObjectInteger*) obj)->cmpLE(this);
        break;
    case TYPE_DECIMAL:
        ret = (double)m_value > ((ObjectDecimal*) obj)->getValue();
        break;
    default:
        ret = false;
    }
    return ret;
}


bool ObjectString::cmpEQ(const Object* obj) const
{
    bool ret = false;
    switch (obj->getType())
    {
    case TYPE_STRING:
        ret = (m_value == ((ObjectString*) obj)->getValue());
        break;
    default:
        ret = false;
    }
    return ret;
}

bool ObjectString::cmpNE(const Object* obj) const
{
    bool ret = true;
    switch (obj->getType())
    {
    case TYPE_STRING:
        ret = (m_value != ((ObjectString*) obj)->getValue());
        break;
    default:
        ret = true;
    }
    return ret;
}

bool ObjectString::cmpLE(const Object* obj) const
{
    bool ret = false;
    switch (obj->getType())
    {
    case TYPE_STRING:
        ret = m_value <= ((ObjectString*) obj)->getValue();
        break;
    default:
        ret = false;
    }
    return ret;
}

bool ObjectString::cmpLT(const Object* obj) const
{
    bool ret = false;
    switch (obj->getType())
    {
    case TYPE_STRING:
        ret = m_value < ((ObjectString*) obj)->getValue();
        break;
    default:
        ret = false;
    }
    return ret;
}

bool ObjectString::cmpGE(const Object* obj) const
{
    bool ret = false;
    switch (obj->getType())
    {
    case TYPE_STRING:
        ret = m_value >= ((ObjectString*) obj)->getValue();
        break;
    default:
        ret = false;
    }
    return ret;
}

bool ObjectString::cmpGT(const Object* obj) const
{
    bool ret = false;
    switch (obj->getType())
    {
    case TYPE_STRING:
        ret = m_value > ((ObjectString*) obj)->getValue();
        break;
    default:
        ret = false;
    }
    return ret;
}