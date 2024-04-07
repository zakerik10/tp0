#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"

	char* message = malloc(sizeof(char) * 100);
	strcpy(message, "Hola! Soy un log");

	logger = iniciar_logger();

	log_info(logger, message);


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	// Usando el config creado previamente, leemos los valores del config y los
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	// Loggeamos el valor de config

	// char *current_dir = getcwd(NULL, 0);
    // // printf("El directorio actual es %s\n", current_dir);
	// char msj[100];
	// sprintf(msj, "El directorio actual es %s, ${workspaceFolder}/bin/${workspaceFolderBasename} \n", current_dir);
	// printf(msj);
	// strcpy(message, msj);
	// log_info(logger, message);

	config = iniciar_config();

	if (config == NULL) {
		// ¡No se pudo crear el config!
		// Terminemos el programa
		strcpy(message, "No se encontro el archivo config");
		log_info(logger, message);
		exit(EXIT_FAILURE);
	}

	valor = buscar_en_config_y_loggear(logger, config, "CLAVE");
	ip = buscar_en_config_y_loggear(logger, config, "IP");
	puerto = buscar_en_config_y_loggear(logger, config, "PUERTO");

	/* ---------------- LEER DE CONSOLA ---------------- */

	//leer_consola(logger);
	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	
	conexion = crear_conexion(ip, puerto);
	// Enviamos al servidor el valor de CLAVE como mensaje

	//send(conexion, &valor, sizeof(char*), 0);
	enviar_mensaje(valor, conexion);

	// Armamos y enviamos el paquete
	//paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente

	free(message);
}

t_log* iniciar_logger()
{

	char* file = malloc(sizeof(char) * 20);
	char* process_name = malloc(sizeof(char) * 30);
	bool is_active_console;
	t_log_level level;

	strcpy(file, "./tp0.log");
	strcpy(process_name, "proccess");

	is_active_console = true;
	level = LOG_LEVEL_INFO;

	t_log* nuevo_logger;
	nuevo_logger = log_create(file, process_name, is_active_console, level);

	free(file);
	free(process_name);
	return nuevo_logger;
}

t_config* iniciar_config()
{
	char* path = malloc(sizeof(char) * 100);
	strcpy(path, "../cliente.config");
	t_config* nuevo_config;
	nuevo_config = config_create(path);
	free(path);
	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	leido = readline("> ");

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío
	while((*leido) != '\0')
	{
		log_info(logger, leido);
		leido = readline("> ");
	}
	// ¡No te olvides de liberar las lineas antes de regresar!
	free(leido);
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;

	// Leemos y esta vez agregamos las lineas al paquete


	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!

}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config)
	  con las funciones de las commons y del TP mencionadas en el enunciado */
	free(logger);
	config_destroy(config);
}

char* buscar_en_config_y_loggear(t_log* logger, t_config* config, char* nombre) {
	char* valor_devuelto;
	if (config_has_property(config, nombre)) {
		valor_devuelto = config_get_string_value(config, nombre);
		log_info(logger, valor_devuelto);
	}
	return valor_devuelto;
}
