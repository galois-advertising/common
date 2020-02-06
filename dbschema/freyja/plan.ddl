{$
#include <iostream>
#include <vector>
$}

handlername = galois;
namespace=galois::freyja;

create datatable plan_table {
    property {
        type = HashTable;
    };
    plan_id : uint32_t;
    user_id : uint32_t;
    region : uint64_t;
    (plan_id) : uint64key, primary_key;
};

create dataupdator plan_view -> plan_table{
    property {
        udf = plan_view_to_plan_table;
    };
};