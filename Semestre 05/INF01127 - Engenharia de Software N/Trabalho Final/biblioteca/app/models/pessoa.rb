class Pessoa < ActiveRecord::Base
  belongs_to :pessoaTipo
  has_many :emprestimo
  has_many :multa
end
