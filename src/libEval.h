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

#ifndef SA_LIBEVAL_H
#define SA_LIBEVAL_H

#include <stdint.h>
#include <stddef.h>

namespace shellanything
{
  /// <summary>
  /// Evaluates a text expression and calculates the result.
  /// </summary>
  /// <param name="expression_string">The text expression to evaluate.</param>
  /// <param name="output">The output double value of the result expression.</param>
  /// <param name="error_buffer">The output error description, if compilation of expression fails.</param>
  /// <param name="error_size">The size in bytes of the error buffer.</param>
  /// <returns>Returns true if the evaluation is successfull. Returns false otherwise.</returns>
  bool Evaluate(const char * expression_string, double * result, char * error_buffer, size_t error_size);

  /// <summary>
  /// Evaluates a boolean text expression as a true or false value.
  /// </summary>
  /// <param name="expression_string">The text expression to evaluate.</param>
  /// <param name="output">The output bool value of the result expression.</param>
  /// <param name="error_buffer">The output error description, if compilation of expression fails.</param>
  /// <param name="error_size">The size in bytes of the error buffer.</param>
  /// <returns>Returns true if the evaluation is successfull. Returns false otherwise.</returns>
  bool Evaluate(const char * expression_string, bool * result, char * error_buffer, size_t error_size);

  /// <summary>
  /// Evaluates a text expression and calculates the result.
  /// </summary>
  /// <param name="expression_string">The text expression to evaluate.</param>
  /// <param name="output">The output double value of the result expression.</param>
  /// <returns>Returns true if the evaluation is successfull. Returns false otherwise.</returns>
  inline bool Evaluate(const char * expression_string, double * result) { return Evaluate(expression_string, result, NULL, 0); }

  /// <summary>
  /// Evaluates a boolean text expression as a true or false value.
  /// </summary>
  /// <param name="expression_string">The text expression to evaluate.</param>
  /// <param name="output">The output bool value of the result expression.</param>
  /// <returns>Returns true if the evaluation is successfull. Returns false otherwise.</returns>
  inline bool Evaluate(const char * expression_string, bool * result) { return Evaluate(expression_string, result, NULL, 0); }

} //namespace shellanything

#endif //SA_LIBEVAL_H
