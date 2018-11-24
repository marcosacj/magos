/*!
 * Canvas class implementation.
 * @file canvas.cpp
 */

#include <stdexcept>
#include <iostream>

#include "canvas.h"

using Nat = std::size_t;

namespace canvas {

    /*!
     * Deep copy of the canvas.
     * @param clone The object we are copying from.
     */
    Canvas::Canvas( const Canvas & clone )
    {
        m_width = clone.m_width;
        m_height = clone.m_height;
        m_line_thikness = clone.m_line_thikness;

        m_pixels = new component_t [ m_height * m_width * 3 ];
        std::memcpy( m_pixels, clone.m_pixels, m_height * m_width * 3 );
    }


    /*!
     * @param source The object we are copying information from.
     * @return A reference to the `this` object.
     */
    Canvas& Canvas::operator=( const Canvas & source )
    {
        m_width = source.m_width;
        m_height = source.m_height;
        m_line_thikness = source.m_line_thikness;

        m_pixels = new component_t [ m_height * m_width * 3 ];
        std::memcpy( m_pixels, source.m_pixels, m_height * m_width * 3 );

        return *this;
    }

    void Canvas::clear( const Color& color )
    {

        for ( Nat pix{0u} ; pix < (m_height * m_width) ; pix++ ){

            for ( Nat channel{0u} ; channel < 3 ; channel++ ){
                *(m_pixels + pix*3 + channel) = color.channels[channel];
            }

        }

    }

    /*!
     * @throw `std::invalid_argument()` it the pixel coordinate is located outside the canvas.
     * @param p The 2D coordinate of the pixel we want to know the color of.
     * @return The pixel color.
     */
    Color Canvas::pixel( coord_type x, coord_type y ) const
    {

        component_t * pix{ m_pixels + 3*coord2index(x, y) };

        Color c{ *(pix + 0), *(pix + 1), *(pix + 2) };

        return c;

    }


    /*!
     * @note Nothing is done if the  pixel coordinate is located outside the canvas.
     * @param p The 2D coordinate of the pixel we want to change the color.
     * @param c The color.
     */
    void Canvas::pixel( coord_type x, coord_type y, const Color& c )
    {

        for ( Nat channel{0u} ; channel < 3 ; channel++ ){

            *(m_pixels + coord2index(x, y)*3 + channel) = c.channels[channel];

        }

    }


    /*!
     * Draws on the canvas a horizontal line.
     * @param p The 2D coordinate of the initial pixel of the line.
     * @param length The horizontal length of the line in pixels.
     */
    void Canvas::hline( coord_type x, coord_type y, size_t length, const Color& color )
    {
        
        // for each pixel desired
        for ( Nat pix{0u} ; pix < length ; pix++ ){

            // redraw line as many times as is the thickness
            for ( Nat thc{0u} ; thc < m_line_thikness ; thc++ ){

                pixel(x + pix, y + thc, color);

            }

        }

    }

    /*!
     * Draws on the canvas a vertical line.
     * @param p The 2D coordinate of the initial pixel of the line.
     * @param length The vertical length of the line in pixels.
     */
    void Canvas::vline( coord_type x, coord_type y, size_t length, const Color& color )
    {
        // TODO

        for ( Nat pix{0u} ; pix < length ; pix++ ){

            for ( Nat thc{0u} ; thc < m_line_thikness ; thc++ ){

                pixel(x + thc, y + pix, color);

            }

        }

    }

    /*!
     * Draws on the canvas a filled box. The origin of the box is the top-left corner.
     * The box is compose of horizontal lines, drawn top to bottom.
     * @param p The 2D coordinate of the initial pixel of the box (top-left corner).
     * @param width The box's width in pixels.
     * @param height The box's heigth in pixels.
     */
    void Canvas::box( coord_type x, coord_type y, size_t width, size_t height , const Color& color)
    {

        for ( Nat w{0u} ; w < width ; w++ ){

            for ( Nat h{0u} ; h < height ; h++ ){

                pixel(x + w, y + h, color);

            }

        }

    }

    Nat Canvas::coord2index( coord_type x, coord_type y ) const {
        return y*m_width + x;
    }

}

//================================[ canvas.cpp ]================================//
