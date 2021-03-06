/*
 * carregador.c
 *
 *  Created on: 21/01/2011
 *      Author: lucas
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "carregador.h"
#include "methods.h"
#include "mnemonics.h"
#include "instructions.h"
#include "jvmerr.h"

#define WHERE "Loader"


char *base_path = "/Users/celio/UnB/workspace/JVM/src/";


struct ClassFile **classArray = NULL;
static_struct *classStaticArray = NULL;
int32_t numClasses = 0;


/*!
 * Carrega uma classe pelo seu nome \a class_name.
 * Será carregada para o vetor classArray no novo índice (numClasses -1).
 * \return Class Index
 */
int32_t loadClass(char *class_name){

	int32_t i, classIndex;
	char *path;
	method_info *staticMethod;

	if (class_name == NULL) return -1;

	/* procura em classArray se a classe já foi carregada */
	for (i = 0; i < numClasses; i++){
		if (strcmp(class_name, getClassName(classArray[i])) == 0)
			return i;
	}

	/* aumenta o vetor classArray */
	numClasses++;
	classIndex = numClasses;
	classArray = realloc(classArray, (classIndex*sizeof(struct ClassFile *)));
	classStaticArray = realloc(classStaticArray, (classIndex*sizeof(static_struct)));

	/* cria o path completo para o arquivo da classe base_path + class_name + .class */
	path = malloc(strlen(base_path) + strlen(class_name) + 7);
	if (strstr(class_name,".class") != NULL)
	  sprintf(path, "%s%s", base_path, class_name);
	else
	  sprintf(path, "%s%s.class", base_path, class_name);

	/* lê a nova classe */
	if ((classArray[classIndex-1] = read_class_file(path)) == NULL)
		fatalErrorMsg(WHERE, "Não foi possível abrir arquivo informado.");

	classStaticArray[classIndex-1].class_name = malloc(strlen(class_name)+1);
	memcpy(classStaticArray[classIndex-1].class_name, class_name, strlen(class_name));
	classStaticArray[classIndex-1].fields_count = classArray[classIndex-1]->fields_count;
	classStaticArray[classIndex-1].value = malloc(classArray[classIndex-1]->fields_count * sizeof(u8));

	/* Executa o método de Init Static caso tenha */
	if ((staticMethod = getInitStaticMethod(classArray[classIndex-1])) != NULL) {
		#ifdef DEBUG
		printf("\nClass: %s\n", class_name);
		#endif
		prepareMethod(classArray[classIndex-1], staticMethod);
		runMethod();
	}

	/* carrega a superclasse da classe carregada */
	loadClass(getParentName(classArray[classIndex-1]));

	return classIndex-1;
}


/*!
 * Retorna string com nome da classe a partir de ponteiro para ClassFile
 */
char *getClassName(struct ClassFile *class){
	u2 this_class = class->this_class;

	u2 name_index = ((struct CONSTANT_Class_info*)class->constant_pool[this_class-1])->name_index;

	return getName( class , name_index );
}


/*!
 * Retorna string com nome da super classe a partir de ponteiro para ClassFile
 */
char *getParentName(struct ClassFile *class){

	u2 super_class, name_index, length;
	u1 *name;
	char *class_name;

	super_class = class->super_class;

	if (super_class == 0) return NULL;

	name_index = ((struct CONSTANT_Class_info*)(class->constant_pool[super_class-1]))->name_index;

	length = ((struct CONSTANT_Utf8_info*) (class->constant_pool[name_index-1]))->length;
	name = ((struct CONSTANT_Utf8_info*) (class->constant_pool[name_index-1]))->bytes;

	class_name = malloc(sizeof(u2) * length+1);

	strncpy(class_name, (char *)name, length);
	class_name[length] = '\0';

	return class_name;
}


/*!
 * Retorna ponteiro pra ClassFile a partir de string \a class_name.
 */
struct ClassFile * getClassByName(char *class_name){

	int i;

	if (!class_name)
		return NULL;

	for (i = 0; i < numClasses; i++){
		if (strcmp(class_name, getClassName(classArray[i])) == 0)
			return classArray[i];
	}

	return NULL;
}

/*
 * Não consegui colocar essas definicoes no .h, nao sei o motivo.
 * Entao tive q fazer esses dois getters.
 */
struct ClassFile * getClassByIndex(int index){
	if (index >= numClasses) {
		return NULL;
	}
	return classArray[index];
}

int getNumClasses(){
	return numClasses;
}

int32_t getFieldIndexByNameAndDesc(char *class_name, char *name, u2 name_len, char *desc, u2 desc_len) {

	int32_t i;
	struct ClassFile *main_class;
	u1 *m_name, *m_desc;
	u2 m_name_len, m_desc_len;

	main_class = getClassByName(class_name);

	if (!main_class) {
		return -2;
	}

	/* Procura pelo Field de acordo com o nome e o desc */
	for (i = 0; main_class && i < main_class->fields_count; i++){

		m_name = ((struct CONSTANT_Utf8_info *)(main_class->constant_pool[(main_class->fields[i].name_index-1)]))->bytes;
		m_name_len = ((struct CONSTANT_Utf8_info *)(main_class->constant_pool[(main_class->fields[i].name_index-1)]))->length;

		m_desc = ((struct CONSTANT_Utf8_info *)(main_class->constant_pool[(main_class->fields[i].descriptor_index-1)]))->bytes;
		m_desc_len = ((struct CONSTANT_Utf8_info *)(main_class->constant_pool[(main_class->fields[i].descriptor_index-1)]))->length;

		if (name_len != m_name_len)
			continue;
		if (desc_len != m_desc_len)
			continue;

		if ((strncmp((char *)name, (char *)m_name , m_name_len) == 0)
				&& (strncmp((char *)desc, (char *)m_desc , m_desc_len) == 0))
			return i;
	}

	return -1;
}

int32_t getClassIndex(struct ClassFile *class_file) {
	int i;

	for (i = 0; i < numClasses; i++) {
		if (classArray[i] == class_file) {
			return i;
		}
	}

	return -1;
}

u8 getStaticFieldValue(int32_t class_index, int32_t field_index) {
	return classStaticArray[class_index].value[field_index];
}

void setStaticFieldValue(int32_t class_index, int32_t field_index, u8 value) {
	classStaticArray[class_index].value[field_index] = value;
}
