{$
#include <iostream>
#include <vector>
$}

handlername = galois;
namespace=galois::freyja;

create datatable idea_table {
    property {
        type = HashTable;
    };
    idea_id : uint64_t;
    unit_id : uint64_t;
    plan_id : uint32_t;
    user_id  : uint32_t;
    title: array char[constant::max_title_len];
    description : array char[constant::max_description_len];
    (idea_id) : uint64key, primary_key;
};

create dataupdator idea_view -> idea_table {
    property {
        udf = idea_view_to_idea_table;
    };
};