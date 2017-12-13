#ifndef IO_FLAGS_H_
#define IO_FLAGS_H_

template<typename EnumType>
class IoFLags
{
public:
    typedef EnumType enum_type;
    typedef const IoFLags<EnumType>& MaskType;
    
    inline IoFLags(EnumType flag);
    /*! \brief Modifying bitwise OR operator.
    *
    * Sets as value the bitwise OR of this and \p other.
    */
    inline IoFLags<EnumType>& operator |= (EnumType other);
    inline IoFLags<EnumType>& operator |= (IoFLags<EnumType> other);

      
    /*! \brief Bitwise AND operator.
    *
    * Returns flags that are the bitwise AND of this and \p mask.
    */
    inline IoFLags<EnumType> operator&(EnumType mask) const;
    inline IoFLags<EnumType> operator&(MaskType mask) const;
    
    /*! \brief Clears a flag.
    */
    inline IoFLags<EnumType>& clear (EnumType value);
    
    /*! \brief Cast to the enum type.
    *
    * The internal <tt>int</tt> representation is simply cast to the
    * enum type, without any additional checks.
    */
    inline operator EnumType() const;
        
private:
    unsigned int flags_;
    IoFLags(int flags, bool) :   flags_(flags) {}
    inline static IoFLags<EnumType> createFromInt(int flags) 
    {
        return IoFLags(flags, false);
    }
};

template<typename EnumType> 
IoFLags<EnumType>::IoFLags(EnumType flag)
    : flags_(flag)
{
}

template<typename EnumType>
IoFLags<EnumType> & IoFLags<EnumType>::operator|=(EnumType other)
{
    flags_ |= other;
    return *this;
}

template<typename EnumType> 
IoFLags<EnumType> & IoFLags<EnumType>::operator|=(IoFLags<EnumType> other)
{
    flags_ |= other.flags_;
    return *this;
}

template<typename EnumType>
IoFLags<EnumType> IoFLags<EnumType>::operator&(EnumType mask) const
{
    return IoFLags<EnumType>::createFromInt(flags_ & (unsigned)mask);
}

template<typename EnumType>
IoFLags<EnumType> IoFLags<EnumType>::operator&(MaskType mask) const
{
    flags_ &= (unsigned)mask;
    return *this;
}

template<typename EnumType> 
IoFLags<EnumType> & IoFLags<EnumType>::clear(EnumType value)
{
    flags_ &= ~value;
    return *this;
}

template<typename EnumType>
IoFLags<EnumType>::operator EnumType() const
{
    return static_cast<EnumType>(flags_);
}

#endif
