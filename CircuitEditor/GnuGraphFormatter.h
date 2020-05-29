#pragma once

#include <iomanip>
#include <sstream>

namespace GnuPlot
{
	struct GnuGraphFormatter
	{
		template <typename T>
		std::string to_string_precision(const T input, const int n)
		{
			std::ostringstream out;
			out << std::setprecision(n) << input;
			return out.str();
		}

		template <typename T>
		typename std::enable_if<std::is_floating_point<T>::value, std::string>::type
			format(const T input)
		{
			//return std::to_string(input) + " ";
			return to_string_precision(input, 12) + " ";
		}

		template <typename T, typename... Trest>
		typename std::enable_if<std::is_floating_point<T>::value, std::string>::type
			format(const T input, const Trest... rest)
		{
			std::string result = format(input);
			result += format(rest...);
			return result;
		}

		template <typename T> // for std::container<double> or Eigen::Vector
		typename std::enable_if<!std::is_floating_point<T>::value, std::string>::type
			format(const T& input)
		{
			std::string result;
			for (int i = 0; i < input.size(); ++i)
				result += format(input[i]);

			return result;
		}

		template <typename T, typename... Trest> // for std::container<double> or Eigen::Vector
		typename std::enable_if<!std::is_floating_point<T>::value, std::string>::type
			format(const T & input, const Trest & ... rest)
		{
			std::string result = format(input);
			result += format(rest...);
			return result;
		}
	};
}