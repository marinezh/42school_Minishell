char *get_env_value(t_env *env_list, const char *key)
{
	//printf("Searching for environment key: '%s'\n", key);
	while (env_list)
	{
		char *temp_key = ft_strdup(env_list->key); // Create a temporary copy to manipulate
		if (!temp_key)
			return NULL;
		
		char *equals = ft_strchr(temp_key, '=');
		if (equals)
			*equals = '\0'; // Remove equals sign if present
			
		printf("Comparing with: '%s' (original: '%s')\n", temp_key, env_list->key);
		if (ft_strcmp(temp_key, key) == 0) // Compare without equals sign
		{
			printf("MATCH FOUND! Value: '%s'\n", env_list->value);
			free(temp_key);
			return env_list->value;
		}
		free(temp_key);
		env_list = env_list->next;
	}
	printf("KEY NOT FOUND in environment\n");
	return NULL;
}