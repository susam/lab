export VAULT_ADDR=http://127.0.0.1:8200/

vault secrets enable kv
vault kv put kv/corp/hr/alice city=london country=uk
vault kv get kv/corp/hr/alice
vault kv get -mount kv corp/hr/alice
read

vault secrets enable -path=zone1 kv
vault kv put zone1/corp/hr/alice id=101 role=admin
vault kv get zone1/corp/hr/alice
vault kv get -mount zone1 corp/hr/alice
read

vault secrets enable -path=zone2/access/policy kv
vault kv put zone2/access/policy/corp/hr/alice id=101 policy=hr
vault kv get zone2/access/policy/corp/hr/alice
vault kv get -mount zone2/access/policy corp/hr/alice
read

# Error: * preflight capability check returned 403, please ensure
# client's policies grant access to path "zone2/acc
vault kv get -mount zone2/access policy/corp/hr/alice

vault kv get -mount zone2/access/policy/corp/hr alice
