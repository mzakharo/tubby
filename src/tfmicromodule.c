#include <tfmicromodule.h>

STATIC MP_DEFINE_CONST_FUN_OBJ_2(fc_obj, fc);

STATIC const mp_rom_map_elem_t tfmicro_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_tfmicro) },
    { MP_ROM_QSTR(MP_QSTR_fc), MP_ROM_PTR(&fc_obj) },
};
STATIC MP_DEFINE_CONST_DICT(tfmicro_module_globals, tfmicro_module_globals_table);

// Define module object.
const mp_obj_module_t tfmicro_user_cmodule = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&tfmicro_module_globals,
};

// Register the module to make it available in Python.
MP_REGISTER_MODULE(MP_QSTR_tfmicro, tfmicro_user_cmodule);
