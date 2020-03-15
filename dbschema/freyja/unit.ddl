{$
#include <iostream>
#include <vector>
#include "databus_event.pb.h"
$}

handlername = freyja_env;
namespace=galois::freyja;

create dataview unit_view on gbus::unit_event {
    property {
        udf = unit_view_udf;
    };
    user_id : uint32_t;
    plan_id : uint32_t;
    unit_id : uint32_t;
    region : uint32_t;
    unit_name : array char[1024u];
    derivative {
        unit_name_sign: uint64_t, from(unit_name);
    };
};

create datatable unit_table {
    property {
        type = HashTable;
    };
    user_id : uint32_t;
    plan_id : uint32_t;
    unit_id : uint32_t;
    unit_name_sign: uint64_t;
    (user_id, plan_id, unit_id) : uint32key, primary_key;
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