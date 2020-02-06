{$
#include <iostream>
#include <vector>
$}

handlername = galois;
namespace=galois::freyja;

create dataview plan_view on gbus::plan_event {
    user_id : uint32_t;
    plan_id : uint32_t;
    region : uint64_t;
    plan_name: array char[1024u];
};

create datatable plan_table {
    property {
        type = HashTable;
    };
    user_id : uint32_t;
    plan_id : uint32_t;
    region : uint64_t;
    plan_name: array char[1024u];
    (user_id, plan_id) : uint64key, primary_key;
};

create dataupdator plan_view -> plan_table{
    property {
        udf = plan_view_to_plan_table;
    };
};