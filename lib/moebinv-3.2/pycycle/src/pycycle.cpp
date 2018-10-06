#include <boost/python/module.hpp>
namespace pycycle {
// Forward declarations.
void wrap_cycle();
} // !namespace pycycle 

BOOST_PYTHON_MODULE( ccycle)
{
	using namespace boost::python;
	using namespace pycycle;
	
	wrap_cycle();
}
