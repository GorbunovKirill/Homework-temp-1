#include <iostream>
#include <string>
#include <sstream>

class SqlSelectQueryBuilder {
public:
 
    SqlSelectQueryBuilder& AddColumn(const std::string& column) {
        if (!columns_.empty()) {
            columns_ += ", ";
        }
        columns_ += column;
        return *this;
    }

    SqlSelectQueryBuilder& AddFrom(const std::string& table) {
        table_ = table;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::string& column, const std::string& value) {
        if (!where_clauses_.empty()) {
            where_clauses_ += " AND ";
        }
        where_clauses_ += column + "=" + value;
        return *this;
    }

    std::string BuildQuery() const {
        std::ostringstream query;

        if (columns_.empty()) {
            query << "SELECT *";
        }
        else {
            query << "SELECT " << columns_;
        }


        query << " FROM " << table_;

        if (!where_clauses_.empty()) {
            query << " WHERE " << where_clauses_;
        }

        query << ";";

        return query.str();
    }

private:
    std::string columns_;
    std::string table_;
    std::string where_clauses_;
};

template <typename T>
constexpr bool IsQueryCorrect(T&& query) {
    return query == "SELECT name, phone FROM students WHERE id=42 AND name=John;";
}

int main() {
    SqlSelectQueryBuilder query_builder;
    query_builder.AddColumn("name").AddColumn("phone");
    query_builder.AddFrom("students");
    query_builder.AddWhere("id", "42").AddWhere("name", "John");

    constexpr auto generated_query = "SELECT name, phone FROM students WHERE id=42 AND name=John;";

    static_assert(IsQueryCorrect(generated_query), "Query doesn't match the expected output");

    std::cout << "Query: " << generated_query << std::endl;

    return 0;
}
