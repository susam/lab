export VAULT_ADDR=http://127.0.0.1:8200/

vault kv get secret/alice
read; echo

vault kv put secret/alice city=london country=uk interest=music interest=theatre
vault kv get secret/alice
read; echo

vault kv put secret/alice city=oxford
vault kv get secret/alice
read; echo

vault kv delete secret/alice
vault kv get secret/alice
