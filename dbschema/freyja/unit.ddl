{$
#include <iostream>
#include <vector>
$}

handlername = galois;
namespace=galois::freyja;

create datatable unit_table {

    property {
        type = HashTable;
    };
    plan_id : uint32_t;
    unit_id : uint64_t;
    (unit_id) : uint64key, primary_key;
};

create dataupdator unit_view -> xdv_table {
    property {
        udf = unit_view_to_xdv_table;
    };
};

create dataupdator unit_view -> unit_table {
    property {
        udf = unit_view_to_unit_table;
    };
};