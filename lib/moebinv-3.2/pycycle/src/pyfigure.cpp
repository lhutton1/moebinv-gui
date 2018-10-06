#include <boost/python/module.hpp>
namespace pyfigure {
// Forward declarations.
void wrap_figure();
} // !namespace pyfigure 

BOOST_PYTHON_MODULE(cfigure)
{
	using namespace boost::python;
	using namespace pyfigure;
	
	wrap_figure();
}
