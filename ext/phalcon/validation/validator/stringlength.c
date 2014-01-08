
#ifdef HAVE_CONFIG_H
#include "../../../ext_config.h"
#endif

#include <php.h>
#include "../../../php_ext.h"
#include "../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/exception.h"
#include "kernel/operators.h"
#include "kernel/string.h"
#include "kernel/array.h"
#include "ext/spl/spl_exceptions.h"


/*
 +------------------------------------------------------------------------+
 | Phalcon Framework                                                      |
 +------------------------------------------------------------------------+
 | Copyright (c) 2011-2013 Phalcon Team (http://www.phalconphp.com)       |
 +------------------------------------------------------------------------+
 | This source file is subject to the New BSD License that is bundled     |
 | with this package in the file docs/LICENSE.txt.                        |
 |                                                                        |
 | If you did not receive a copy of the license and are unable to         |
 | obtain it through the world-wide-web, please send an email             |
 | to license@phalconphp.com so we can send you a copy immediately.       |
 +------------------------------------------------------------------------+
 | Authors: Andres Gutierrez <andres@phalconphp.com>                      |
 |          Eduar Carvajal <eduar@phalconphp.com>                         |
 +------------------------------------------------------------------------+
 */
/**
 * Phalcon\Validation\Validator\StringLength
 *
 * Validates that a string has the specified maximum and minimum constraints
 *
 *<code>
 *use Phalcon\Validation\Validator\StringLength as StringLength;
 *
 *$validation->add('name_last', new StringLength(array(
 *      'max' => 50,
 *      'min' => 2,
 *      'messageMaximum' => 'We don\'t like really long names',
 *      'messageMinimum' => 'We want more than just their initials'
 *)));
 *</code>
 *
 */
ZEPHIR_INIT_CLASS(Phalcon_Validation_Validator_StringLength) {

	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Validation\\Validator, StringLength, phalcon, validation_validator_stringlength, phalcon_validation_validator_ce, phalcon_validation_validator_stringlength_method_entry, 0);

	zend_class_implements(phalcon_validation_validator_stringlength_ce TSRMLS_CC, 1, phalcon_validation_validatorinterface_ce);

	return SUCCESS;

}

/**
 * Executes the validation
 *
 * @param Phalcon\Validation validation
 * @param string field
 * @return boolean
 */
PHP_METHOD(Phalcon_Validation_Validator_StringLength, validate) {

	zval *field = NULL;
	zval *validation, *field_param = NULL, *isSetMin, *isSetMax, *value, *length, *message = NULL, *minimum, *maximum, *label = NULL, *replacePairs = NULL, *_0, *_1, _2, *_3 = NULL, *_4 = NULL, *_5 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &validation, &field_param);

		if (Z_TYPE_P(field_param) != IS_STRING) {
				zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'field' must be a string") TSRMLS_CC);
				RETURN_MM_NULL();
		}

		field = field_param;



	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "min", 1);
	ZEPHIR_INIT_VAR(isSetMin);
	zephir_call_method_p1(isSetMin, this_ptr, "issetoption", _0);
	ZEPHIR_INIT_BNVAR(_0);
	ZVAL_STRING(_0, "max", 1);
	ZEPHIR_INIT_VAR(isSetMax);
	zephir_call_method_p1(isSetMax, this_ptr, "issetoption", _0);
	if ((!zephir_is_true(isSetMin) && !zephir_is_true(isSetMax))) {
		ZEPHIR_THROW_EXCEPTION_STR(phalcon_validation_exception_ce, "A minimum or maximum must be set");
		return;
	}
	ZEPHIR_INIT_VAR(value);
	zephir_call_method_p1(value, validation, "getvalue", field);
	ZEPHIR_INIT_BNVAR(_0);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "allowEmpty", 1);
	zephir_call_method_p1(_0, this_ptr, "issetoption", _1);
	if (zephir_is_true(_0) && ZEPHIR_IS_EMPTY(value)) {
		RETURN_MM_BOOL(1);
	}
	ZEPHIR_INIT_BNVAR(_1);
	ZVAL_STRING(_1, "label", 1);
	ZEPHIR_INIT_VAR(label);
	zephir_call_method_p1(label, this_ptr, "getoption", _1);
	if (ZEPHIR_IS_EMPTY(label)) {
		ZEPHIR_CPY_WRT(label, field);
	}
	ZEPHIR_INIT_VAR(length);
	ZEPHIR_SINIT_VAR(_2);
	ZVAL_STRING(&_2, "mb_strlen", 0);
	ZEPHIR_INIT_BNVAR(_1);
	zephir_call_func_p1(_1, "function_exists", &_2);
	if (zephir_is_true(_1)) {
		zephir_call_func_p1(length, "mb_strlen", value);
	} else {
		ZVAL_LONG(length, zephir_fast_strlen_ev(value));
	}
	if (zephir_is_true(isSetMax)) {
		ZEPHIR_INIT_VAR(_3);
		ZVAL_STRING(_3, "max", 1);
		ZEPHIR_INIT_VAR(maximum);
		zephir_call_method_p1(maximum, this_ptr, "getoption", _3);
		if (ZEPHIR_GT(length, maximum)) {
			ZEPHIR_INIT_NVAR(_3);
			ZVAL_STRING(_3, "messageMaximum", 1);
			ZEPHIR_INIT_VAR(message);
			zephir_call_method_p1(message, this_ptr, "getoption", _3);
			ZEPHIR_INIT_VAR(replacePairs);
			array_init_size(replacePairs, Resource id #1749);
			zephir_array_update_string(&replacePairs, SL(":field"), &label, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&replacePairs, SL(":max"), &maximum, PH_COPY | PH_SEPARATE);
			if (ZEPHIR_IS_EMPTY(message)) {
				ZEPHIR_INIT_NVAR(_3);
				ZVAL_STRING(_3, "TooLong", 1);
				ZEPHIR_INIT_NVAR(message);
				zephir_call_method_p1(message, validation, "getdefaultmessage", _3);
			}
			ZEPHIR_INIT_NVAR(_3);
			object_init_ex(_3, phalcon_validation_message_ce);
			ZEPHIR_INIT_VAR(_4);
			zephir_call_func_p2(_4, "strtr", message, replacePairs);
			ZEPHIR_INIT_VAR(_5);
			ZVAL_STRING(_5, "TooLong", 1);
			zephir_call_method_p3_noret(_3, "__construct", _4, field, _5);
			zephir_call_method_p1_noret(validation, "appendmessage", _3);
			RETURN_MM_BOOL(0);
		}
	}
	if (zephir_is_true(isSetMin)) {
		ZEPHIR_INIT_NVAR(_3);
		ZVAL_STRING(_3, "min", 1);
		ZEPHIR_INIT_VAR(minimum);
		zephir_call_method_p1(minimum, this_ptr, "getoption", _3);
		if (ZEPHIR_LT(length, minimum)) {
			ZEPHIR_INIT_NVAR(_3);
			ZVAL_STRING(_3, "messageMinimum", 1);
			ZEPHIR_INIT_NVAR(message);
			zephir_call_method_p1(message, this_ptr, "getoption", _3);
			ZEPHIR_INIT_NVAR(replacePairs);
			array_init_size(replacePairs, Resource id #1751);
			zephir_array_update_string(&replacePairs, SL(":field"), &label, PH_COPY | PH_SEPARATE);
			zephir_array_update_string(&replacePairs, SL(":min"), &minimum, PH_COPY | PH_SEPARATE);
			if (ZEPHIR_IS_EMPTY(message)) {
				ZEPHIR_INIT_NVAR(_3);
				ZVAL_STRING(_3, "TooShort", 1);
				ZEPHIR_INIT_NVAR(message);
				zephir_call_method_p1(message, validation, "getdefaultmessage", _3);
			}
			ZEPHIR_INIT_NVAR(_3);
			object_init_ex(_3, phalcon_validation_message_ce);
			ZEPHIR_INIT_NVAR(_4);
			zephir_call_func_p2(_4, "strtr", message, replacePairs);
			ZEPHIR_INIT_NVAR(_5);
			ZVAL_STRING(_5, "TooShort", 1);
			zephir_call_method_p3_noret(_3, "__construct", _4, field, _5);
			zephir_call_method_p1_noret(validation, "appendmessage", _3);
			RETURN_MM_BOOL(0);
		}
	}
	RETURN_MM_BOOL(1);

}
