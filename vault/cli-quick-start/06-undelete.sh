export VAULT_ADDR=http://127.0.0.1:8200/

vault kv put secret/alice city=london country=uk interest=music interest=theatre
vault kv put secret/alice city=oxford country=uk interest=painting interest=tennis
vault kv get secret/alice
read

vault kv delete secret/alice
vault kv get secret/alice
read

vault kv undelete -versions=2 secret/alice
vault kv get secret/alice
