{$
#include <iostream>
#include <vector>
#include "databus_event.pb.h"
$}

handlername = freyja_env;
namespace=galois::freyja;

create dataview plan_view on gbus::plan_event {
    property {
        udf = plan_view_udf;
    };
    user_id : uint32_t;
    plan_id : uint32_t;
    region : uint64_t;
    plan_name: array char[1024u];
    derivative {
        plan_name_sign: uint64_t, from(plan_name);
    };
};

create datatable plan_table {
    property {
        type = HashTable;
    };
    user_id : uint32_t;
    plan_id : uint32_t;
    region : uint64_t;
    plan_name_sign: uint64_t;
    (user_id, plan_id) : uint64key, primary_key;
};

create dataupdator plan_view -> plan_table {
    property {
        udf = plan_view_to_plan_table;
    };
};


create indextable plan_index on plan_table::plan_id {
    property {
        type = HashTable;
    };
    user_id : uint32_t;
    plan_id : uint32_t;
    region : uint64_t;
    plan_name: array char[1024u];
};

create indexupdator plan_table -> plan_index {};