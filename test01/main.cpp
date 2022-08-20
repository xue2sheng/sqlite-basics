#include <sqlite/connection.hpp>
#include <sqlite/query.hpp>
#include <iostream>

int main()
{
	try {
		sqlite::connection con("test01.db");
		sqlite::query q(con, "SELECT * FROM tblone;");
		boost::shared_ptr<sqlite::result> result = q.get_result();
		while(result->next_row()) std::cout << "word='" << result->get_string(0) << "' value=" << result->get_int(1) << std::endl;
	}
	catch(std::exception const& e)
	{
		std::cerr << "An error occurred: " << e.what() << std::endl;
		return -1;
	}
	return 0;
}
