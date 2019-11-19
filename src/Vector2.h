#pragma once


#include <iostream>

/**
 * Vector2 class that represents two dimensional vector and besic operations with it
 */
struct Vector2 
{
    /**
     * Basic addition between two vectros
     * @param[in] vec Other vector
     * @return Reference to this vector
     */
    Vector2 & Add ( const Vector2 & vec );

    /**
     * Basic subtraction between two vectros
     * @param[in] vec Other vector
     * @return Reference to this vector
     */
    Vector2 & Subtract ( const Vector2 & vec );


    public:
        //! X coordinates of vector
        double x;
        //! Y coordinates of vector
        double y;
        
        Vector2 ();

        /** Vector2 constructor 
         * @param[in] x X coordinate
         * @param[in] y Y coordinate
         */
        Vector2 ( double x, double y );
        
        /**
         * Overloaded + operator sum of two vectors
         * @param[in] v1 First vector
         * @param[in] v2 Second vector
         * @return Reference to this vector
         */
        friend Vector2 operator + ( const Vector2 & v1, const Vector2 & v2 );

        /**
         * Overloaded - operator substraction of two vectors
         * @param[in] v1 First vector
         * @param[in] v2 Second vector
         * @return Reference to this vector
         */
        friend Vector2 operator - ( const Vector2 & v1, const Vector2 & v2 );

        /**
         * Overloaded += operator that adds vector to this vector
         * @param[in] v Other vector to add to this
         * @return Reference to this vector
         */
        Vector2 & operator += ( const Vector2 & v );

        /**
         * Overloaded -= operator that subtracts vector from this vector
         * @param[in] v Other vector to substract from this
         * @return Reference to this vector
         */
        Vector2 & operator -= ( const Vector2 & v );

        /**
         * Overloaded * operatro that multiplies vector by scalar
         * @param[in] vec Other vector
         * @return Reference to this vector
         */
        Vector2 & operator * ( const double & i );

        /**
         * Set both coordinats of vector to zero
         * @return Reference to this vector
         */
        Vector2 & Zero();

        /**
         * Overloaded << operator 
         * @param[in,out] ostr Ostream parameter
         * @param[in] v Vector to be sent to outpout stream
         * @return refrence to output stream
         */
        friend std::ostream & operator << ( std::ostream & ostr, const Vector2 v );
};