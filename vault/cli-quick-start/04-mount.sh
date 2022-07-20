export VAULT_ADDR=http://127.0.0.1:8200/

vault kv get -mount secret alice
read

vault kv put -mount secret alice city=london country=uk interest=music interest=theatre
vault kv get -mount secret alice
read

vault kv put -mount secret alice city=oxford
vault kv get -mount secret alice
read
