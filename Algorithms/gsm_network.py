# python3
import itertools

n, m = map(int, input().split())
edges = [ list(map(int, input().split())) for i in range(m) ]


def exactly_one(v, clauses, colors, variable_count):
    if v not in colors:
        colors[v] = [variable_count, variable_count + 1, variable_count + 2]
        clauses.append("".join("{} ".format(l) for l in colors[v]) + "0")

        for pair in itertools.combinations(colors[v], 2):
            clauses.append("".join("-{} ".format(l) for l in pair) + "0")
        return variable_count + 3
    return variable_count


def print_equisatisfiable_sat_formula():
    variable_count = 1
    colors = {}
    clauses = []

    for a, b in edges:
        variable_count = exactly_one(a, clauses, colors, variable_count)
        variable_count = exactly_one(b, clauses, colors, variable_count)

        for idx in range(3):
            clauses.append("-{} -{} 0".format(colors[a][idx], colors[b][idx]))

    print(len(clauses), variable_count + 1)
    print('\n'.join(clause for clause in clauses))


print_equisatisfiable_sat_formula()
