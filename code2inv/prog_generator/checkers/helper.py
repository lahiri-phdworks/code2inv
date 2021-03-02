def process_model_string(model: str):
    # COMMENT : iterate over all crashes inputs and extract test failures
    vals = []
    decls = []
    model_val = dict()

    if model == "":
        return None

    cex_type = model.split(":")[0].strip()
    m_list = model.replace(":", ",").split(",")
    for index, elems in enumerate(m_list):
        if (index % 2) == 0:
            vals.append(elems.strip())
        else:
            decls.append(elems.strip())
    vals.pop(0)
    for key, values in zip(decls, vals):
        model_val[f"{key}"] = int(values)
    return [cex_type, model_val]


if __name__ == '__main__':
    print(process_model_string("Pre : sum : 0, n : 101, i : 1, y : 0, i2 : 0"))
