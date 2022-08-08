#include <iostream>
#include <mysql/mysql.h>

struct connection_details {
  const char *server;
  const char *user;
  const char *password;
  const char *database;
  unsigned int port;
};

// MySQL Connection Setup Function
MYSQL *mysql_connection_setup(connection_details mysqlDetails) {
  MYSQL *connection = mysql_init(NULL);

  if (!mysql_real_connect(connection, mysqlDetails.server, mysqlDetails.user, mysqlDetails.password, mysqlDetails.database, mysqlDetails.port, NULL, 0)) {
    std::cout << "Connection Error: " << mysql_error(connection) << std::endl;
    exit(1);
  }

  return connection;
}

// MySQL Execute Query Function
MYSQL_RES* mysql_execute_query(MYSQL *connection, const char *sqlQuery) {
  if (mysql_query(connection, sqlQuery)) {
    std:: cout << "MySQL Query Error: " << mysql_error(connection) << std::endl;
    exit(1);
  }

  return mysql_use_result(connection);
}

int main(int argc, char const *argv[]) {
  MYSQL *connection;
  MYSQL_RES *mysqlResult;
  MYSQL_ROW mysqlRow;

  // Initialize MySQL Connection Details
  struct connection_details mysqlD;
  mysqlD.server = "127.0.0.1";
  mysqlD.user = "forever";
  mysqlD.password = "Security123!@#";
  mysqlD.database = "cppexample";
  mysqlD.port = 3306;

  // Connect to MySQL Database
  connection = mysql_connection_setup(mysqlD);
  mysqlResult = mysql_execute_query(connection, "select * from tblUsers;");

  std::cout << "Displaying database output: " << std::endl;

  // Display Mysql Query Result
  while ((mysqlRow = mysql_fetch_row(mysqlResult)) != NULL) {
    std::cout << mysqlRow[0] << " : " << mysqlRow[1] << " : " << mysqlRow[2] << " : " << mysqlRow[3] << " : " << mysqlRow[4] << " : " << std::endl;
  }

  // Free MySQL
  mysql_free_result(mysqlResult);
  mysql_close(connection);

  return 0;
}