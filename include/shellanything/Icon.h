/**********************************************************************************
 * MIT License
 * 
 * Copyright (c) 2018 Antoine Beauchamp
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *********************************************************************************/

#ifndef SA_ICON_H
#define SA_ICON_H

#include <string>
#include <vector>

namespace shellanything
{

  /// <summary>
  /// Icon class encapsulate the path to a system's icon.
  /// </summary>
  class Icon
  {
  public:
    /// <summary>
    /// Invalid index within a file.
    /// </summary>
    static const int INVALID_ICON_INDEX = -1;

    Icon();
    Icon(const Icon & icon);
    virtual ~Icon();

    /// <summary>
    /// Copy operator
    /// </summary>
    const Icon & operator =(const Icon & icon);

    /// <summary>
    /// Returns true if the icon have a valid path and index.
    /// </summary>
    /// <returns>Returns true if the icon have a valid path and index. Returns false otherwise.</returns>
    bool isValid() const;

    /// <summary>
    /// Getter for the 'fileextension' parameter.
    /// </summary>
    const std::string & getFileExtension() const;

    /// <summary>
    /// Setter for the 'fileextension' parameter.
    /// </summary>
    void setFileExtension(const std::string & iFileExtension);

    /// <summary>
    /// Getter for the 'path' parameter.
    /// </summary>
    const std::string & getPath() const;

    /// <summary>
    /// Setter for the 'path' parameter.
    /// </summary>
    void setPath(const std::string & iPath);

    /// <summary>
    /// Getter for the 'index' parameter.
    /// </summary>
    const int & getIndex() const;

    /// <summary>
    /// Setter for the 'index' parameter.
    /// </summary>
    void setIndex(const int & iIndex);

  private:
    std::string mFileExtension;
    std::string mPath;
    int mIndex;
  };

} //namespace shellanything

#endif //SA_ICON_H
