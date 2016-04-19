/* -----------------------------------------------------------------------------

	Copyright (c) 2006 Simon Brown                          si@sjbrown.co.uk

	Permission is hereby granted, free of charge, to any person obtaining
	a copy of this software and associated documentation files (the 
	"Software"), to	deal in the Software without restriction, including
	without limitation the rights to use, copy, modify, merge, publish,
	distribute, sublicense, and/or sell copies of the Software, and to 
	permit persons to whom the Software is furnished to do so, subject to 
	the following conditions:

	The above copyright notice and this permission notice shall be included
	in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
	OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
	IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
	CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
	TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
	SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
	
   -------------------------------------------------------------------------- */
   
#ifndef SQUISH_PNG_H
#define SQUISH_PNG_H

#include <string>
#include <squish.h>

//! Base class to make derived classes non-copyable
class NonCopyable
{
public:
	NonCopyable() {}

private:
	NonCopyable(NonCopyable const&);
	NonCopyable& operator=(NonCopyable const&);
};

//! Memory object.
class Mem : NonCopyable
{
public:
	Mem() : m_p(0) {}
	explicit Mem(int size) : m_p(new squish::u8[size]) {}
	~Mem() { delete[] m_p; }

	void Reset(int size)
	{
		squish::u8 *p = new squish::u8[size];
		delete m_p;
		m_p = p;
	}

	squish::u8* Get() const { return m_p; }

private:
	squish::u8* m_p;
};

//! Represents a DXT compressed image in memory.
struct DxtData
{
	int width;
	int height;
	int format;		//!< Either kDxt1, kDxt3 or kDxt5.
	Mem data;
	bool isColour;
	bool isAlpha;
};

   //! Represents an uncompressed RGBA image in memory.
class Image
{
public:
	Image();

	void LoadPng(std::string const& fileName);
	void SavePng(std::string const& fileName) const;

	void Decompress(DxtData const& dxt);
	void Compress(DxtData& dxt, int flags) const;

	double GetRmsError(Image const& image) const;

private:
	int m_width;
	int m_height;
	bool m_isColour;	//!< Either colour or luminance.
	bool m_isAlpha;		//!< Either alpha or not.
	Mem m_pixels;
};

#endif // ndef SQUISH_PNG_H

